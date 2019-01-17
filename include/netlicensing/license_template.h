#ifndef __LICENSE_TEMPLATE_H__
#define __LICENSE_TEMPLATE_H__

#include <list>

#include "netlicensing/entity.h"

namespace netlicensing {

  class LicenseTemplate : public BaseEntity {
  private:
    String_t name_i;
    String_t licenseType_i;//TODO(AY): change type to LicenseType
    String_t productModuleNumber_i;
    String_t price_i;//TODO(AY): change type to Double ?
    String_t currency_i;//TODO(AY): change type to Currency
    Boolean_t automatic_i = false;
    Boolean_t hidden_i = false;
    Boolean_t hideLicenses_i = false;

  public:
    LicenseTemplate() : name_i(), licenseType_i(), productModuleNumber_i(),
    price_i(), currency_i(), automatic_i(), hidden_i(), hideLicenses_i() { }

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }

    void setLicenseType(const String_t& licenseType) {
      licenseType_i = licenseType;
    }

    const String_t& getLicenseType() const {
      return licenseType_i;
    }

    void setProductModuleNumber(const String_t& productModuleNumber) {
      productModuleNumber_i = productModuleNumber;
    }

    const String_t& getProductModuleNumber() const {
      return productModuleNumber_i;
    }

    void setPrice(const String_t& price) {
      price_i = price;
    }

    const String_t& getPrice() const {
      return price_i;
    }

    void setCurrency(const String_t& currency) {
      currency_i = currency;
    }

    const String_t& getCurrency() const {
      return currency_i;
    }

    void setAutomatic(const Boolean_t automatic) {
      automatic_i = automatic;
    }

    const Boolean_t getAutomatic() const {
      return automatic_i;
    }

    void setHidden(const Boolean_t hidden) {
      hidden_i = hidden;
    }

    const Boolean_t getHidden() const {
      return hidden_i;
    }

    void setHideLicenses(const Boolean_t hideLicenses) {
      hideLicenses_i = hideLicenses;
    }

    const Boolean_t getHideLicenses() const {
      return hideLicenses_i;
    }

    String_t toString() const {
      std::string name(this->getName());
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());
      std::string licenseType(this->getLicenseType());
      std::string productModuleNumber(this->getProductModuleNumber());
      std::string price(this->getPrice());
      std::string currency(this->getCurrency());
      Boolean_t automatic(this->getAutomatic());
      Boolean_t hidden(this->getHidden());
      Boolean_t hideLicenses(this->getHideLicenses());

      std::stringstream ss;
      ss << "LicenseTemplate [";
      ss << "name: ";
      ss << name;
      ss << ", ";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << ", ";
      ss << "licenseType: ";
      ss << licenseType;
      ss << ", ";
      ss << "productModuleNumber: ";
      ss << productModuleNumber;
      ss << ", ";
      ss << "price: ";
      ss << price;
      ss << ", ";
      ss << "currency: ";
      ss << currency;
      ss << ", ";
      ss << "automatic: ";
      ss << automatic.toString();
      ss << ", ";
      ss << "hidden: ";
      ss << hidden.toString();
      ss << ", ";
      ss << "hideLicenses: ";
      ss << hideLicenses.toString();
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __LICENSE_TEMPLATE_H__
