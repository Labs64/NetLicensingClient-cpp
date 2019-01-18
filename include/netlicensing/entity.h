#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <map>
#include <sstream>
#include <string>

#include "netlicensing/datatypes.h"

namespace netlicensing {

/*
template<typename S, typename T>
void lexical_cast(T& t, const S& s) {
  std::stringstream stream;
  if (!(stream << s) || !(stream >> t) || !(stream >> std::ws).eof()) {
    throw std::bad_cast();
  }
}

inline void assign(std::string& target, const std::string& source) {
  target = source;
}

inline void assign(bool& target, const std::string& source) {
  if (source == "true") target = true;
  else if (source == "false") target = false;
  else throw std::logic_error("Value can not be interpret as logic");
}

inline void assign(int& target, const std::string& source) {
  lexical_cast(target, source);
}
*/

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

/*
class BaseEntityConverter {
  BaseEntity& baseEntity_i;
public:
  BaseEntityConverter(BaseEntity& baseEntity) : baseEntity_i(baseEntity) {}
  bool convert(const std::string& property, const std::string value) {
    if (property == "number") {
      baseEntity_i.setNumber(value);
      return true;
    } else if (property == "active") {
      baseEntity_i.setActive(value == "true");
      return true;
    }
    return false;
  }
};

template<typename E>
class EntityConverter : public BaseEntityConverter {
};
*/

}

#endif //__ENTITY_H__
