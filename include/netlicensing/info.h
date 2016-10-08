#ifndef __INFO_H__
#define __INFO_H__

#include <string>

namespace netlicensing {

class Info {
  std::string id_i;
  std::string type_i;
  std::string value_i;
  
public:
  Info(const std::string& id, const std::string& type, const std::string& value)
    : id_i(id), type_i(type), value_i(value) { }

  const std::string& getId() const {
    return id_i;
  }

  const std::string& getType() const {
    return type_i;
  }

  const std::string& getValue() const {
    return value_i;
  }

  std::string to_string() const {
    return id_i + "[" + type_i + "]: " + value_i;
  }
};

}

#endif //__INFO_H__
