#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <string>
#include <list>

namespace netlicensing {

/**
* @brief configure your connection to rest server using this Context class
*
*/
class Context {
 public:
  typedef std::list<std::pair<std::string, std::string> > parameters_type;
  Context();
  ~Context();

  void set_username(const std::string&);
  void set_password(const std::string&);
  void set_base_url(const std::string&);
  std::string username() const;
  std::string password() const;
  std::string base_url() const;

  std::string post(const std::string& endpoint, const parameters_type& params);
  std::string get(const std::string& endpoint, const parameters_type& params);
  std::string del(const std::string& endpoint, const parameters_type& params);
 private:
  Context(const Context&);
  Context& operator=(const Context&);
  class NetworkService;
  NetworkService* network_service_;

  std::string username_;
  std::string password_;
  std::string base_url_;
};
}

#endif //__CONTEXT_H__