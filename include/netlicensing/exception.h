#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <list>
#include <stdexcept>
#include "netlicensing/info.h"

namespace netlicensing {

/**
* @brief Network external error 
*
* @param msg message from network provider
* @param code error code from network provider
* @param details error details(if exists)
*
*/
class ServiceException : public std::runtime_error {
 private:
  int code_;
 public:
  ServiceException(const std::string& msg, int code, const std::string details) : std::runtime_error(msg + " details: " + details),
    code_(code) {}

  int return_code() const {
    return code_;
  }
};

/**
* @brief REST provider exception
*
* @param msg message from REST server
* @param code http return code
*
*/
class RestException : public std::runtime_error {
 private:
  int code_;
  std::list<Info> details_;
 public:
  RestException(const std::list<Info>& details, int code) : 
    std::runtime_error("REST error"), code_(code), details_(details) {}
 
  virtual ~RestException() throw() {}

  int http_code() const {
    return code_;
  }

  const std::list<Info> get_details() const {
    return details_;
  }
};

class MalformedArgumentsException : public std::runtime_error {
 public:
   MalformedArgumentsException(const std::string& msg) : std::runtime_error(msg) {}
};

}  // namespace netlicensing

#endif  // __EXCEPTION_H__
