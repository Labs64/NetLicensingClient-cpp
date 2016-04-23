#include "netlicensing/entity.h"
#include <sstream>

namespace netlicensing {

bool Entity::add_property(const std::string& key, const std::string& value) {
  std::pair<user_properties_map::iterator, bool> ins = user_defined_properties_.insert(std::make_pair(key, value));
  return ins.second;
}

std::string Entity::get_property(const std::string& key) const {
  user_properties_map::const_iterator itr = user_defined_properties_.find(key);
  if (itr != user_defined_properties_.end()) return itr->second;
  return "";
}

std::string Entity::to_string() const {
  std::stringstream ss;
  for (auto kv : user_defined_properties_) {
    ss << kv.first << "{" << kv.second << "} ";
  }

  return ss.str();
}

}