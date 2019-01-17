#ifndef __LICENSEE_H__
#define __LICENSEE_H__

#include "netlicensing/entity.h"

namespace netlicensing {

  class Licensee : public BaseEntity {
    String_t name_i;
    String_t productNumber_i;

  public:
    Licensee() : name_i(), productNumber_i() {}

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }

    void setProductNumber(const String_t& productNumber) {
      productNumber_i = productNumber;
    }

    const String_t& getProductNumber() const {
      return productNumber_i;
    }
    
    String_t toString() const {
      std::string name(this->getName());
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());
      std::string productNumber(this->getProductNumber());

      std::stringstream ss;
      ss << "Licensee [";
      ss << "name: ";
      ss << name;
      ss << ", ";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << ", ";
      ss << "productNumber: ";
      ss << productNumber;
      ss << "]";
      return ss.str();
    }

  };

}  // namespace netlicensing

#endif  // __LICENSEE_H__
