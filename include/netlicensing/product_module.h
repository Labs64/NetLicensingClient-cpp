#ifndef __PRODUCT_MODULE_H__
#define __PRODUCT_MODULE_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class ProductModule : public BaseEntity {
  private:
    String_t name_i;
    String_t licensingModel_i;
    String_t productNumber_i;

  public:
    ProductModule() : name_i(), licensingModel_i(), productNumber_i() { }

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }

    void setLicensingModel(const String_t& licensingModel) {
      licensingModel_i = licensingModel;
    }

    const String_t& getLicensingModel() const {
      return licensingModel_i;
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
      std::string licensingModel(getLicensingModel());
      std::string productNumber(getProductNumber());

      std::stringstream ss;
      ss << "ProductModule [";
      ss << NAME << ": " << name << ", ";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString() << ", ";
      ss << LICENSING_MODEL << ": " << licensingModel << ", ";
      ss << PRODUCT_NUMBER << ": " << productNumber;

      for (const auto& pair : getProperties()) {
          ss << ", " << pair.first << ": " << pair.second.toString();
      }

      ss << "]";
      return ss.str();
    }
  };

}

#endif // __PRODUCT_MODULE_H__
