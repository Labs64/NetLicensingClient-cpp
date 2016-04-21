#ifndef __VALIDATION_RESULT_H__
#define __VALIDATION_RESULT_H__

#include "netlicensing/entity.h"
#include <list>

namespace netlicensing {

struct ValidationProperty {
  Entity values;
  std::string name_;
  std::list<ValidationProperty*> sub_properties_;

  ~ValidationProperty() {
    for (auto p : sub_properties_) {
      delete p;
    }
  }
};

struct ValidationResult {
  Entity value;
  std::string product_module_number_;
  std::list<ValidationProperty> properties;
};

}

#endif //__VALIDATION_RESULT_H__
