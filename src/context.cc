#include "netlicensing/context.h"
#include "netlicensing/version.h"
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
size_t write_callback(void *data, size_t size, size_t nmemb, void *userdata) {
  std::string *r = reinterpret_cast<std::string *>(userdata);
  r->append(reinterpret_cast<char *>(data), size * nmemb);
  return (size * nmemb);
}

size_t read_callback(void *data, size_t size, size_t nmemb, void *userdata) {
  // Get upload struct
  std::pair<const char*, size_t> *body = reinterpret_cast<std::pair<const char*, size_t>*>(userdata);

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
class Context::NetworkService {
 public:
  static const char*  m_user_agent;
  static const char*  m_accept_type;
  static const char*  m_content_type;

  enum RequestType {
    GET,
    POST,
    PUT,
    DEL
  };

  NetworkService() : handle_(NULL) {
    handle_ = curl_easy_init();
  }

  ~NetworkService() {
    if (handle_) curl_easy_cleanup(handle_);
  }

#define MAKE_HEADER(name, value) (std::string(name) + ": " + std::string(value)).c_str()

  std::string post(const std::string& url,
    const Context::parameters_type& params,
    const std::string username,
    const std::string password) {
    return send_request(POST, url, params, username, password);
  }

  std::string get(const std::string& url,
    const Context::parameters_type& params,
    const std::string username,
    const std::string password) {
    return send_request(GET, url, params, username, password);
  }

  std::string del(const std::string& url,
    const Context::parameters_type& params,
    const std::string username,
    const std::string password) {
    return send_request(DEL, url, params, username, password);
  }

  std::string send_request(
    RequestType type,
    const std::string& url,
    const Context::parameters_type& params,
    const std::string username,
    const std::string password) {
    std::string response_body;
    std::string request_body;
    std::pair<const char*, size_t>  request_body_info;
    curl_slist *header = NULL;

    // Reset libcurl
    curl_easy_reset(handle_);

    // Debug output
    curl_easy_setopt(handle_, CURLOPT_VERBOSE, 1);

    // Set user agent
    curl_easy_setopt(handle_, CURLOPT_USERAGENT, NetworkService::m_user_agent);

    // Set query URL
    curl_easy_setopt(handle_, CURLOPT_URL, url.c_str());

    // Set proxy
    //curl_easy_setopt(m_handle, CURLOPT_PROXY, proxy_.c_str());

    // generate request body from parameters list
    if (type == POST || type == PUT) {
      std::list<std::string>  joined_params;
      std::transform(params.begin(), params.end(), std::back_inserter(joined_params), pair2string());
      request_body = std::accumulate(joined_params.begin(), joined_params.end(), request_body, join_sep());
      request_body_info = std::make_pair(request_body.c_str(), request_body.length());

      curl_easy_setopt(handle_, CURLOPT_POST, 1L);      
      curl_easy_setopt(handle_, CURLOPT_POSTFIELDSIZE, request_body.length());
        
      // Set read callback function and parameter for function
      curl_easy_setopt(handle_, CURLOPT_READFUNCTION, &read_callback);
      curl_easy_setopt(handle_, CURLOPT_READDATA, &request_body_info);
      header = curl_slist_append(header, MAKE_HEADER("Content-Type", NetworkService::m_content_type));
    }

    switch (type) {
    case PUT:
      curl_easy_setopt(handle_, CURLOPT_CUSTOMREQUEST, "PUT");
      break;
    case DEL:
      curl_easy_setopt(handle_, CURLOPT_CUSTOMREQUEST, "DELETE");
      break;
    default:
      break;
    }

    // Set callback function
    curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, &write_callback);

    // Set data object to pass to callback function
    curl_easy_setopt(handle_, CURLOPT_WRITEDATA, &response_body);

    // Specify authentication information
    if (!username.empty()) {
      curl_easy_setopt(handle_, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
      curl_easy_setopt(handle_, CURLOPT_USERNAME, username.c_str());
      curl_easy_setopt(handle_, CURLOPT_PASSWORD, password.c_str());
    }

    // Set content negotiation header
    header = curl_slist_append(header, MAKE_HEADER("Accept", NetworkService::m_accept_type));
    curl_easy_setopt(handle_, CURLOPT_HTTPHEADER, header);

    // Prepare buffer for error messages
    char errors[CURL_ERROR_SIZE];
    curl_easy_setopt(handle_, CURLOPT_ERRORBUFFER, &errors);

    // Perform the actual query
    CURLcode res = curl_easy_perform(handle_);

    // Free header list
    curl_slist_free_all(header);

    // Handle unexpected internal errors
    //if (res != 0)
    //{
    //    throw ResponseError(curl_easy_strerror(res), res, errors);
    //}

    // Handle server-side erros
    long http_code = 0;
    curl_easy_getinfo(handle_, CURLINFO_RESPONSE_CODE, &http_code);
    //check_http_error(type, endpoint, http_code, response_body);
    return response_body;
  }

 private:
  CURL*   handle_;
};

const char* Context::NetworkService::m_user_agent = "netlicensing_cpp/" NETLICENSING_VERSION;
const char* Context::NetworkService::m_content_type = "application/x-www-form-urlencoded";
const char* Context::NetworkService::m_accept_type = "application/json";


Context::Context() : network_service_(NULL) {
  network_service_ = new NetworkService();
}

Context::~Context() {
  delete network_service_;
}

void Context::set_username(const std::string& username) {
  username_ = username;
}

void Context::set_password(const std::string& password) {
  password_ = password;
}

void Context::set_base_url(const std::string& url) {
  base_url_ = url;
  // TODO - check parameters here and throw appropriate exception!

  assert(!base_url_.empty());
  if (base_url_.at(base_url_.length() - 1) == '/') {
    base_url_.erase(base_url_.length() - 1, 1);
  }
}

std::string Context::username() const { return username_; }
std::string Context::password() const { return password_; }
std::string Context::base_url() const { return base_url_; }

std::string Context::post(const std::string& endpoint, const parameters_type& params) {
  assert(!endpoint.empty());
  assert(network_service_ != NULL);
  return network_service_->post(base_url_ + "/" + endpoint, params, username_, password_);
}

std::string Context::get(const std::string& endpoint, const parameters_type& params) {
  assert(!endpoint.empty());
  assert(network_service_ != NULL);
  return network_service_->get(base_url_ + "/" + endpoint, params, username_, password_);
}

std::string Context::del(const std::string& endpoint, const parameters_type& params) {
  assert(!endpoint.empty());
  assert(network_service_ != NULL);
  return network_service_->del(base_url_ + "/" + endpoint, params, username_, password_);
}

}
