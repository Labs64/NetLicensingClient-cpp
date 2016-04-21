#ifndef __VALIDATION_RESULT_H__
#define __VALIDATION_RESULT_H__

#include "netlicensing/entity.h"
#include <memory>
#include <list>

namespace netlicensing {

struct ValidationProperty {
  Entity values;
  std::string name_;
  std::list<std::shared_ptr<ValidationProperty> > next_properties_;  
};

struct ValidationResult {  
  std::string product_module_number_;
  std::string product_module_name_;
  std::string licensing_model_;
  std::list<std::shared_ptr<ValidationProperty> > properties_;  
};

}

#endif //__VALIDATION_RESULT_H__
