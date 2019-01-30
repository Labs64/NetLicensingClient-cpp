#ifndef __LICENSEE_H__
#define __LICENSEE_H__

#include "netlicensing/constants.h"
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
    
    std::string toString() const {
      std::string name(getName());
      std::string number(getNumber());
      Boolean_t active(getActive());
      std::string productNumber(getProductNumber());

      std::stringstream ss;
      ss << "Licensee [";
      ss << NAME << ": " << name << ", ";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString() << ", ";
      ss << PRODUCT_NUMBER << ": " << productNumber;
      ss << "]";
      return ss.str();
    }

  };

}  // namespace netlicensing

#endif  // __LICENSEE_H__
