#include "netlicensing/validation_result.h"
#include <sstream>
#include <iostream>

namespace netlicensing {

std::string Composition::toString() const {
  std::stringstream ss;
  if (!value_i) {
    ss << "{";
    if (properties_i.empty()) {
      ss << "<null>";
    } else {
      bool first = true;
      for (auto prop : properties_i) {
        if (first) {
          first = false;
        } else {
          ss << ", ";
        }
        ss << prop.first << "=" << prop.second.toString();
      }
    }
    ss << "}";
  } else {
    ss << *value_i;
  }
  return ss.str();
}

std::string ValidationResult::toString() const {
  std::stringstream ss;
  ss << "ValidationResult [";
  bool first = true;
  for (auto validationEntry : validations_i) {
    if (first) {
      first = false;
    } else {
      ss << ", ";
    }
    ss << "ProductModule<";
    ss << validationEntry.first;
    ss << ">";
    ss << validationEntry.second.toString();
  }
  ss << "]";
  return ss.str();
}

}
