#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <map>
#include <sstream>
#include <string>

#include "netlicensing/datatypes.h"

namespace netlicensing {

class BaseEntity {
private:
  String_t number_i;
  Boolean_t active_i = true;
  std::map<std::string, String_t> properties_i;

public:
  void setNumber(const String_t& number) {
    number_i = number;
  }

  const String_t& getNumber() const {
    return number_i;
  }
  
  void setActive(Boolean_t active) {
    active_i = active;
  }

  Boolean_t getActive() const {
    return active_i;
  }

  // Methods for working with custom properties

  const std::map<std::string, String_t>& getProperties() const {
    return properties_i;
  }

  void addProperty(const std::string& property, String_t value) {
    properties_i[property] = value;
  }

  void removeProperty(const std::string& property) {
    properties_i.erase(property);
  }
};
}

#endif //__ENTITY_H__
