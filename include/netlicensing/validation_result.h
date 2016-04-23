#ifndef __VALIDATION_RESULT_H__
#define __VALIDATION_RESULT_H__

#include "netlicensing/entity.h"
#include "netlicensing/info.h"

namespace netlicensing {

/**
*   validation nested property- can be recursive
*/
struct ValidationProperty : public RecursiveList<ValidationProperty> {
  Entity values;
  void add_property(const std::string& name, const std::string& value) {
    if (RecursiveList<ValidationProperty>::add_property(name, value)) return;
    values.add_property(name, value);
  }

  std::string to_string() const;
};


/*
* main validation result
*/
struct ValidationResult {
  std::string product_module_number_;
  std::string product_module_name_;
  std::string licensing_model_;

  typedef ValidationProperty PropertyType;
  std::list<std::shared_ptr<ValidationProperty> > properties_;
  void add_property(const std::string& name, const std::string& value);
  void add_list(std::shared_ptr<PropertyType> ptr);
  std::string to_string() const;
};

}

#endif //__VALIDATION_RESULT_H__
