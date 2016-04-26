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
 public:
   typedef ValidationProperty PropertyType;
 private:
  std::string product_module_number_;
  std::string product_module_name_;
  std::string licensing_model_;

  std::list<std::shared_ptr<ValidationProperty> > properties_;
 public:
  void add_property(const std::string& name, const std::string& value);
  void add_list(std::shared_ptr<PropertyType> ptr);
  std::string to_string() const;

  std::string getProductModuleNumber() const { return product_module_number_; }
  std::string getProductModuleName() const { return product_module_name_; }
  std::string getLicensingModel() const { return licensing_model_; }
  std::list<std::shared_ptr<ValidationProperty> > getProperties() const { return properties_; }
};

}

#endif //__VALIDATION_RESULT_H__
