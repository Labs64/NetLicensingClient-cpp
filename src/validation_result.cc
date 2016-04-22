#include "netlicensing/validation_result.h"

namespace netlicensing {

void ValidationResult::add_property(const std::string& name, const std::string& value) {
  if (name == "productModuleNumber") product_module_number_ = value;
  else if (name == "productModuleName") product_module_name_ = value;
  else if (name == "licensingModel") licensing_model_ = value;
}

void ValidationResult::add_list(std::shared_ptr<PropertyType> ptr) {
  properties_.push_back(ptr);
}

}
