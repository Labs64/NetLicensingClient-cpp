#include "netlicensing/validation_result.h"
#include <sstream>

namespace netlicensing {

std::string ValidationProperty::to_string() const {
  std::stringstream ss;
  ss << "ProductModule <" << name_ << "\n";
  ss << values.to_string();
  //for (auto nested : nested_lists_) {
  //  ss << nested->nested_lists_.;
  //}
  ss << ">\n";
  return ss.str();
}

void ValidationResult::add_property(const std::string& name, const std::string& value) {
  if (name == "productModuleNumber") product_module_number_ = value;
  else if (name == "productModuleName") product_module_name_ = value;
  else if (name == "licensingModel") licensing_model_ = value;
}

void ValidationResult::add_list(std::shared_ptr<PropertyType> ptr) {
  properties_.push_back(ptr);
}

std::string ValidationResult::to_string() const {
  std::stringstream ss;
  for (auto vp : properties_) {
    ss << vp->to_string();
  }

  return ss.str();
}

}
