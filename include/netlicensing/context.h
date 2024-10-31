#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "netlicensing/converters.h"

namespace netlicensing {

/**
 * @brief Configure your connection to rest server using this Context class
 *
 */
class Context {
 public:
  enum SecurityMode {
    BASIC_AUTHENTICATION,
    APIKEY_IDENTIFICATION,
    ANONYMOUS_IDENTIFICATION
  };

  Context();
  ~Context();

  void set_username(const std::string&);
  void set_password(const std::string&);
  void set_base_url(const std::string&);
  void set_api_key(const std::string&);
  void set_vendor_number(const std::string&);
  void set_security_mode(SecurityMode);

  std::string username() const;
  std::string password() const;
  std::string base_url() const;
  std::string api_key() const;
  std::string vendor_number() const;
  SecurityMode security_mode() const;

  std::string post(const std::string& endpoint, const parameters_type& params, long& http_code);
  std::string get(const std::string& endpoint, const parameters_type& params, long& http_code);
  std::string del(const std::string& endpoint, const parameters_type& params, long& http_code);
 private:
  const std::string& user() const;
  const std::string& pass() const;
  Context(const Context&);
  Context& operator=(const Context&);
  class NetworkService;
  NetworkService* network_service_;

  std::string username_;
  std::string password_;
  std::string base_url_;
  std::string api_key_;
  std::string vendor_number_;
  SecurityMode mode_;
};

// for unit testing
extern std::string url_with_parameters(const std::string& url, const parameters_type& params);

/**
 * @brief returns url encoded string
 */
extern std::string escape_string(const std::string& s);
}

#endif //__CONTEXT_H__
