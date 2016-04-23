#include "netlicensing/info.h"

namespace netlicensing {

void Info::add_property(const std::string& name, const std::string& value) {
  if (name == "value") value_ = value;
  else if (name == "id") id_ = value;
  else if (name == "type") type_ = value;
}

std::string Info::to_string() const {
  return type_ + ": " + value_;
}

}