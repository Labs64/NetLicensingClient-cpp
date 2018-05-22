#ifndef __VALIDATION_RESULT_H__
#define __VALIDATION_RESULT_H__

#include <map>
#include <memory>
#include <string>

namespace netlicensing {

/**
 *   validation nested property- can be recursive
 */
class Composition {
  std::shared_ptr<std::string> value_i;
  std::map<std::string, Composition> properties_i;

public:
  Composition() : value_i() { }
  Composition(const std::string& value) : value_i(std::make_shared<std::string>(value)) { }
  
  std::shared_ptr<std::string> getValue() const { return value_i; }

  const std::map<std::string, Composition>& getProperties() {
    return properties_i;
  }

  void put(const std::string& name, const std::string& value) {
    properties_i.insert(std::make_pair(name, Composition(value)));
  }

  void put(const std::string& name, const Composition& value) {
    properties_i.insert(std::make_pair(name, value));
  }
  
  std::shared_ptr<std::string> get(const std::string& name) const {
    auto prop = properties_i.find(name);
    if (prop == properties_i.end()) {
      return std::shared_ptr<std::string>();
    }
    return prop->second.getValue();
  }

  std::string toString() const;
};


/*
* main validation result
*/
class ValidationResult {
  std::map<std::string, Composition> validations_i;
  time_t ttl;

public:
  ValidationResult() { }
  

  const std::map<std::string, Composition>& getValidations() {
    return validations_i;
  }

  const time_t& getTtl() {
    return ttl;
  }

  void setTtl(const time_t& resTtl) {
    ttl = resTtl;
  }

  const Composition& getProductModuleValidation(const std::string& productModuleNumber) {
    static Composition empty;
    auto validation = validations_i.find(productModuleNumber);
    if (validation == validations_i.end()) {
      return empty;
    }
    return validation->second;
  }
  
  void setProductModuleValidation(const std::string& productModuleNumber,
                                  const Composition& productModuleValidation) {
    validations_i.insert(std::make_pair(productModuleNumber, productModuleValidation));
  }

  std::string toString() const;
};

}

#endif  // __VALIDATION_RESULT_H__
