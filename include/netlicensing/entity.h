#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
#include <map>

namespace netlicensing {

class Entity {
private:
  typedef std::map<std::string, std::string> user_properties_map;
  user_properties_map user_defined_properties_;
public:
  bool add_property(const std::string& key, const std::string& value);
  std::string get_property(const std::string& key) const;
};

}

#endif //__ENTITY_H__