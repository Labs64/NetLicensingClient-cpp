#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <stdint.h>
#include <sstream>
#include <string>

#include "netlicensing/exception.h"

namespace netlicensing {

  // This is a simplified version of std::optional (or boost::optional) to avoid dependency
  // on not yet widely supported C++17 or external library (boost).
  template <typename T>
  class Optional {
    bool available_i;
    T value_i;

  public:
    Optional() : available_i(false), value_i() {}
    Optional(T value) : available_i(true), value_i(value) {}
    Optional(const char* value);

    bool operator()() const { return available_i; }

    operator T() const { return value_i; }

    std::string toString() const;
  };


  // TODO(2K): Precision is currently fixed at 2 digits after decimal point, make variable
  class FixedPoint {
    int64_t value_i;

  public:
    FixedPoint(const std::string& value) {
      if (value == "0") {
        value_i = 0;
      } else if ((value.length() > 3) && (value[value.length() - 3] == '.')) {
        // TODO(2K): too primitive parsing - improve
        std::string rawValue = value;
        rawValue.erase(value.length() - 3, 1);
        std::istringstream is(rawValue);
        is >> value_i;
      } else {
        throw MalformedArgumentsException("Not supported formatting for fixed point value");
      }
    }

    std::string toString() const {
      std::ostringstream os;
      os << value_i;
      std::string sValue = os.str();
      sValue.insert(sValue.length() - 2, ".");
      return sValue;
    }
  };


  typedef Optional<std::string> String_t;
  typedef Optional<FixedPoint> Decimal_t;
  typedef Optional<bool> Boolean_t;

  template<>
  inline Optional<std::string>::Optional(const char* value)
    : available_i(true), value_i(value) { }

  template<>
  inline std::string Optional<std::string>::toString() const {
    return value_i;
  }

  template<>
  inline std::string Optional<FixedPoint>::toString() const {
    return value_i.toString();
  }

  template<>
  inline Optional<bool>::Optional(const char* value)
    : available_i(true), value_i(std::string(value) == "true") { }

  template<>
  inline std::string Optional<bool>::toString() const {
    return value_i ? "true" : "false";
  }

  typedef std::list<std::pair<std::string, std::string> > parameters_type;

}  // namespace netlicensing

#endif  // __DATATYPES_H__