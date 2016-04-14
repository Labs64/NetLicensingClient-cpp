#include "netlicensing/service.hpp"
#include "netlicensing/version.hpp"
#include "curl/curl.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <cassert>

#include <sstream>

namespace netlicensing {

    // Initialize user agent string
    const char *service::user_agent_ = "netlicensing_cpp/" NETLICENSING_VERSION;

    // Initialize content type string
    const char *service::content_type_ = "application/json";

    // TODO - remove this strange structure?
    // Struct used for sending data
    typedef struct
    {
        const char *data;
        size_t length;
    } RequestBody;

    // Helper macros
#define MAKE_HEADER(name, value) (std::string(name) + ": " + std::string(value)).c_str()
#define CURL_HANDLE static_cast<CURL *>(instance().curl_handle_)

    // Initialize curl
    service::service()
    {
        curl_handle_ = static_cast<void *>(curl_easy_init());

        if (!curl_handle_)
        {
            throw ServiceError("Unable to initialize libcurl", 0);
        }

        // Read environment proxy
        read_environment_proxy();
    }

    // Free curl
    service::~service()
    {
        if (curl_handle_)
        {
            curl_easy_cleanup(CURL_HANDLE);
        }
    }

    /**
    * @brief HTTP GET method
    *
    * @param endpoint url to query
    *
    * @return response body
    */
    std::string service::get_(const std::string &endpoint) const
    {
        return send_request(GET, endpoint, "");
    }

    /**
    * @brief HTTP POST method
    *
    * @param endpoint url to query
    * @param data HTTP POST body
    *
    * @return response body
    */
    std::string service::post_(const std::string &endpoint, const std::string &body) const
    {
        return send_request(POST, endpoint, body);
    }

    /**
    * @brief HTTP PUT method
    *
    * @param endpoint url to query
    * @param data HTTP PUT body
    *
    * @return response body
    */
    std::string service::put_(const std::string &endpoint, const std::string &body) const
    {
        return send_request(PUT, endpoint, body);
    }

    /**
    * @brief HTTP DEL method
    *
    * @param endpoint url to query
    *
    * @return response body
    */
    std::string service::del_(const std::string &endpoint) const
    {
        return send_request(DEL, endpoint, "");
    }

    /**
    * @brief URL encode the specified string
    *
    * @param value the string to URL encode
    *
    * @return the URL encoded string
    */
    std::string service::escape_(const std::string &value) const
    {
        char *curl_esc = curl_easy_escape(CURL_HANDLE, value.c_str(), value.size());
        std::string escaped(curl_esc);
        curl_free(curl_esc);

        return escaped;
    }

    /**
    * @brief Add a query parameter to the specified URL
    *
    * @param url the URL to add the parameter to
    * @param param the parameter name
    * @param value the parameter value, will be URL encoded
    *
    * @return the new URL that includes the query parameter
    */
    std::string service::query_param_(const std::string &url, const std::string &param, const std::string &value) const
    {
        std::string query_part;

        if (url.find("http://") == 0 && url.find('/', 7) == std::string::npos)
        {
            query_part += "/";
        }

        if (url.find('?') != std::string::npos)
        {
            query_part += "&";
        }
        else
        {
            query_part += "?";
        }

        query_part += param;
        query_part += "=";
        query_part += escape_(value);

        return url + query_part;
    }
    
    /**
    * @brief wrapper to perform curl request
    *
    * @param type the request type
    * @param endpoint url to query
    * @param data HTTP PUT body
    *
    * @return
    */
    std::string service::send_request(const RequestType &type, const std::string &endpoint, const std::string &body) const
    {
        curl_slist *header = NULL;

        // Create return struct
        std::string response_body;

        // Initialize request body
        RequestBody request_body;
        request_body.data = body.c_str();
        request_body.length = body.size();

        // Reset libcurl
        curl_easy_reset(CURL_HANDLE);

        // Debug output
        //curl_easy_setopt(CURL_HANDLE, CURLOPT_VERBOSE, 1);

        // Set user agent
        curl_easy_setopt(CURL_HANDLE, CURLOPT_USERAGENT, service::user_agent_);

        // Set query URL
        curl_easy_setopt(CURL_HANDLE, CURLOPT_URL, url(endpoint).c_str());

        // Set proxy
        curl_easy_setopt(CURL_HANDLE, CURLOPT_PROXY, proxy_.c_str());

        switch (type)
        {
        case POST:
            // Now specify we want to POST data
            curl_easy_setopt(CURL_HANDLE, CURLOPT_POST, 1L);

            // Set data size
            curl_easy_setopt(CURL_HANDLE, CURLOPT_POSTFIELDSIZE, request_body.length);

            break;

        case PUT:
            // Now specify we want to PUT data
            curl_easy_setopt(CURL_HANDLE, CURLOPT_POST, 1L);
            curl_easy_setopt(CURL_HANDLE, CURLOPT_CUSTOMREQUEST, "PUT");

            // Set data size
            curl_easy_setopt(CURL_HANDLE, CURLOPT_POSTFIELDSIZE, request_body.length);

            break;

        case DEL:
            // Set HTTP DEL METHOD
            curl_easy_setopt(CURL_HANDLE, CURLOPT_CUSTOMREQUEST, "DELETE");

            break;
        }

        switch (type)
        {
        case POST:
        case PUT:
            // Set read callback function
            curl_easy_setopt(CURL_HANDLE, CURLOPT_READFUNCTION, service::read_callback);

            // Set data object to pass to callback function
            curl_easy_setopt(CURL_HANDLE, CURLOPT_READDATA, &request_body);

            // Set content-type header
            header = curl_slist_append(header, MAKE_HEADER("Content-Type", content_type_));

            break;
        }

        // Set callback function
        curl_easy_setopt(CURL_HANDLE, CURLOPT_WRITEFUNCTION, service::write_callback);

        // Set data object to pass to callback function
        curl_easy_setopt(CURL_HANDLE, CURLOPT_WRITEDATA, &response_body);

        // Specify authentication information
        if (!username().empty())
        {
            curl_easy_setopt(CURL_HANDLE, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(CURL_HANDLE, CURLOPT_USERNAME, username().c_str());
            curl_easy_setopt(CURL_HANDLE, CURLOPT_PASSWORD, password().c_str());
        }

        // Set content negotiation header
        header = curl_slist_append(header, MAKE_HEADER("Accept", content_type_));
        curl_easy_setopt(CURL_HANDLE, CURLOPT_HTTPHEADER, header);

        // Prepare buffer for error messages
        char errors[CURL_ERROR_SIZE];
        curl_easy_setopt(CURL_HANDLE, CURLOPT_ERRORBUFFER, &errors);

        // Perform the actual query
        CURLcode res = curl_easy_perform(CURL_HANDLE);

        // Free header list
        curl_slist_free_all(header);

        // Handle unexpected internal errors
        if (res != 0)
        {
            throw ResponseError(curl_easy_strerror(res), res, errors);
        }

        // Handle server-side erros
        long http_code = 0;
        curl_easy_getinfo(CURL_HANDLE, CURLINFO_RESPONSE_CODE, &http_code);

        check_http_error(type, endpoint, http_code, response_body);

        return response_body;
    }

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
    size_t service::write_callback(void *data, size_t size, size_t nmemb, void *userdata)
    {
        std::string *r = reinterpret_cast<std::string *>(userdata);
        r->append(reinterpret_cast<char *>(data), size * nmemb);

        return (size * nmemb);
    }

    /**
    * @brief read callback function for libcurl
    *
    * @param pointer of max size (size*nmemb) to write data to
    * @param size size parameter
    * @param nmemb memblock parameter
    * @param userdata pointer to user data to read data from
    *
    * @return (size * nmemb)
    */
    size_t service::read_callback(void *data, size_t size, size_t nmemb, void *userdata)
    {
        // Get upload struct
        RequestBody *body = reinterpret_cast<RequestBody *>(userdata);

        // Set correct sizes
        size_t curl_size = size * nmemb;
        size_t copy_size = (body->length < curl_size) ? body->length : curl_size;

        // Copy data to buffer
        memcpy(data, body->data, copy_size);

        // Decrement length and increment data pointer
        body->length -= copy_size;
        body->data += copy_size;

        // Return copied size
        return copy_size;
    }

    /**
    * @brief Check whether an error occurred
    *
    * @param type the request type
    * @param http_code the response code
    * @param response_body the response body
    */
    void service::check_http_error(const RequestType &type, const std::string &endpoint, long &http_code, const std::string &response_body)
    {
        // Handle BadRequestError and ValidationError
        if (http_code == 400)
        {
            if (response_body.find("validation_errors") != std::string::npos)
            {
                throw ValidationError(response_body);
            }
            else
            {
                throw BadRequestError(response_body);
            }
        }

        // Handle AuthenticationError
        if (http_code == 401)
        {
            throw AuthenticationError();
        }

        // Handle other errors
        bool http_ok = false;

        switch (type)
        {
        case GET:
            http_ok = (http_code == 200);

            break;

        case POST:
            http_ok = (http_code == 201);

            break;

        case PUT:
            http_ok = (http_code == 200 || http_code == 201);

            break;

        case DEL:
            http_ok = (http_code == 204);

            break;
        }

        if (!http_ok)
        {
            std::stringstream s;
            s << "Server at \"" << url(endpoint) << "\" responded with code " << http_code;

            throw ResponseError(s.str(), http_code, response_body);
        }
    }

    void service::read_environment_proxy()
    {
        if (getenv("HTTP_PROXY"))
        {
            proxy_ = getenv("HTTP_PROXY");
        }
        else
        {
            proxy_.clear();
        }
    }
};
