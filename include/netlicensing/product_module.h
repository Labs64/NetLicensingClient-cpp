#ifndef __PRODUCT_MODULE_H__
#define __PRODUCT_MODULE_H__

#include <list>

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

    String_t toString() const {
      std::string name(this->getName());
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());
      std::string licensingModel(this->getLicensingModel());
      std::string productNumber(this->getProductNumber());

      std::stringstream ss;
      ss << "ProductModule [";
      ss << "name: ";
      ss << name;
      ss << ", ";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << ", ";
      ss << "licensingModel: ";
      ss << licensingModel;
      ss << ", ";
      ss << "productNumber: ";
      ss << productNumber;
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __PRODUCT_MODULE_H__