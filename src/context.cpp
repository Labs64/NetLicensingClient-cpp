#include "netlicensing/context.hpp"
#include "netlicensing/version.hpp"
#include <curl/curl.h>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <cassert>

namespace netlicensing {    

    // http://www.ietf.org/rfc/rfc2396.txt
    // section 2.3
    static const char unreserved_chars[] =
        // when determining if a url needs encoding
        // % should be ok
        "%+"
        // reserved
        ";?:@=&,$/"
        // unreserved (special characters) ' excluded,
        // since some buggy trackers fail with those
        "-_!.~*()"
        // unreserved (alphanumerics)
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
        "0123456789";

    static const char hex_chars[] = "0123456789abcdef";

    // the offset is used to ignore the first characters in the unreserved_chars table.
    std::string escape_string(const char* str, size_t len, size_t offset = 11) {
        assert(str != 0);
        assert(offset < size_t(sizeof(unreserved_chars)) - 1);

        std::string ret;
        for (int i = 0; i < len; ++i) {
            if (std::strchr(unreserved_chars + offset, *str) && *str != 0) {
                ret += *str;
            }
            else {
                ret += '%';
                ret += hex_chars[((unsigned char)*str) >> 4];
                ret += hex_chars[((unsigned char)*str) & 15];
            }
            ++str;
        }

        return ret;
    }

    // trivial escape string
    std::string escape_string(const std::string& s) {
        return escape_string(s.c_str(), s.length());
    }

    // pair to string functor
    struct pair2string {
        std::string operator()(const std::pair<std::string, std::string>& p) {
            return p.first + "=" + escape_string(p.second);
        }
    };

    // join string functor
    struct join_sep {
        std::string operator()(const std::string& s1, const std::string& s2) {
            if (s1.empty()) return s1 + s2;
            return s1 + "&" + s2;
        }
    };


    /**
    * @brief write callback function for libcurl
    *
    * @param data returned data of size (size*nmemb)
    * @param size size parameter
    * @param nmemb memblock parameter
    * @param userdata pointer to user data to save/work with return data
    *
    * @return (size * nmemb)
    */
    size_t write_callback(void *data, size_t size, size_t nmemb, void *userdata)
    {
        std::string *r = reinterpret_cast<std::string *>(userdata);
        r->append(reinterpret_cast<char *>(data), size * nmemb);
        return (size * nmemb);
    }

    size_t read_callback(void *data, size_t size, size_t nmemb, void *userdata) {
        // Get upload struct
        std::pair<const char*, size_t> *body = reinterpret_cast<std::pair<const char*, size_t>* >(userdata);

        // Set correct sizes
        size_t curl_size = size * nmemb;
        size_t copy_size = (std::min)(body->second, curl_size);

        // Copy data to buffer
        memcpy(data, body->first, copy_size);

        // Decrement length and increment data pointer
        body->second -= copy_size;
        body->first += copy_size;

        // Return copied size
        return copy_size;
    }

    /**
    * @brief HTTP network provider class
    *
    */
    class context::network_service {
    public:        
        static const char*  m_user_agent;
        static const char*  m_accept_type;
        static const char*  m_content_type;

        network_service() : m_handle(NULL) {
            m_handle = curl_easy_init();
        }

        ~network_service() {
            if (m_handle) curl_easy_cleanup(m_handle);
        }

#define MAKE_HEADER(name, value) (std::string(name) + ": " + std::string(value)).c_str()

        std::string post(const std::string& url, 
            const context::parameters_type& params, 
            const std::string username, 
            const std::string password) {
            std::string response_body;
            std::string request_body;
            curl_slist *header = NULL;

            // TODO - move it to dedicated function
            std::list<std::string>  joined_params;
            std::transform(params.begin(), params.end(), std::back_inserter(joined_params), pair2string());
            request_body = std::accumulate(joined_params.begin(), joined_params.end(), request_body, join_sep());
            std::pair<const char*, size_t>  request_body_info = std::make_pair(request_body.c_str(), request_body.length());

            // Reset libcurl
            curl_easy_reset(m_handle);

            // Debug output
            curl_easy_setopt(m_handle, CURLOPT_VERBOSE, 1);

            // Set user agent
            curl_easy_setopt(m_handle, CURLOPT_USERAGENT, network_service::m_user_agent);

            // Set query URL
            curl_easy_setopt(m_handle, CURLOPT_URL, url.c_str());

            // Set proxy
            //curl_easy_setopt(m_handle, CURLOPT_PROXY, proxy_.c_str());

            // Now specify we want to POST data
            curl_easy_setopt(m_handle, CURLOPT_POST, 1L);

            // Set data size
            curl_easy_setopt(m_handle, CURLOPT_POSTFIELDSIZE, request_body.length());


            // Set read callback function
            curl_easy_setopt(m_handle, CURLOPT_READFUNCTION, &read_callback);

            // Set data object to pass to callback function
            curl_easy_setopt(m_handle, CURLOPT_READDATA, &request_body_info);

            // Set content-type header
            header = curl_slist_append(header, MAKE_HEADER("Content-Type", network_service::m_content_type));


            // Set callback function
            curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, &write_callback);

            // Set data object to pass to callback function
            curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, &response_body);

            // Specify authentication information
            if (!username.empty())
            {
                curl_easy_setopt(m_handle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
                curl_easy_setopt(m_handle, CURLOPT_USERNAME, username.c_str());
                curl_easy_setopt(m_handle, CURLOPT_PASSWORD, password.c_str());
            }

            // Set content negotiation header
            header = curl_slist_append(header, MAKE_HEADER("Accept", network_service::m_accept_type));
            curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, header);

            // Prepare buffer for error messages
            char errors[CURL_ERROR_SIZE];
            curl_easy_setopt(m_handle, CURLOPT_ERRORBUFFER, &errors);

            // Perform the actual query
            CURLcode res = curl_easy_perform(m_handle);

            // Free header list
            curl_slist_free_all(header);

            // Handle unexpected internal errors
            //if (res != 0)
            //{
            //    throw ResponseError(curl_easy_strerror(res), res, errors);
            //}

            // Handle server-side erros
            long http_code = 0;
            curl_easy_getinfo(m_handle, CURLINFO_RESPONSE_CODE, &http_code);
            //check_http_error(type, endpoint, http_code, response_body);
            return response_body;
        }
        
    private:
        CURL*   m_handle;
    };

    const char* context::network_service::m_user_agent = "netlicensing_cpp/" NETLICENSING_VERSION;
    const char* context::network_service::m_content_type = "application/x-www-form-urlencoded";
    const char* context::network_service::m_accept_type = "application/json";


    context::context() : m_instance(NULL) {
        m_instance = new network_service();
    }

    context::~context() {
        delete m_instance;
    }

    void context::set_username(const std::string& username) {
        m_username = username;
    }

    void context::set_password(const std::string& password) {
        m_password = password;
    }

    void context::set_base_url(const std::string& url) {
        m_base_url = url;
        // TODO - check parameters here and throw appropriate exception!

        assert(!m_base_url.empty());
        if (m_base_url.at(m_base_url.length() - 1) == '/') {
            m_base_url.erase(m_base_url.length() - 1, 1);
        }
    }

    std::string context::username() const { return m_username; }
    std::string context::password() const { return m_password; }
    std::string context::base_url() const { return m_base_url; }

    std::string context::post(const std::string& endpoint, const parameters_type& params) {
        assert(!endpoint.empty());
        assert(m_instance != NULL);
        return m_instance->post(m_base_url + "/" + endpoint, params, m_username, m_password);
    }
}
