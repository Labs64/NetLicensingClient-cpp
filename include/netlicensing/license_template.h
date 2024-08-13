#ifndef __LICENSE_TEMPLATE_H__
#define __LICENSE_TEMPLATE_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class LicenseTemplate : public BaseEntity {
  private:
    String_t name_i;
    LicenseTypeEnum licenseType_i;
    String_t productModuleNumber_i;
    FixedPoint price_i = FixedPoint(0);
    Currency currency_i;
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

    void setLicenseType(const LicenseTypeEnum licenseType) {
      licenseType_i = licenseType;
    }

    const LicenseTypeEnum getLicenseType() const {
      return licenseType_i;
    }

    void setProductModuleNumber(const String_t& productModuleNumber) {
      productModuleNumber_i = productModuleNumber;
    }

    const String_t& getProductModuleNumber() const {
      return productModuleNumber_i;
    }

    void setPrice(const FixedPoint& price) {
      price_i = price;
    }

    const FixedPoint& getPrice() const {
      return price_i;
    }

    void setCurrency(const Currency currency) {
      currency_i = currency;
    }

    const Currency getCurrency() const {
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

    std::string toString() const {
      std::string name(getName());
      std::string number(getNumber());
      Boolean_t active(getActive());
      std::string licenseType(licenseTypeToString(getLicenseType()));
      std::string productModuleNumber(getProductModuleNumber());
      std::string price(getPrice().toString());
      std::string currency(currencyToString(getCurrency()));
      Boolean_t automatic(getAutomatic());
      Boolean_t hidden(getHidden());
      Boolean_t hideLicenses(getHideLicenses());

      std::stringstream ss;
      ss << "LicenseTemplate [";
      ss << NAME << ": " << name << ", ";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString() << ", ";
      ss << LICENSE_TYPE << ": " << licenseType << ", ";
      ss << PRODUCT_MODULE_NUMBER << ": " << productModuleNumber << ", ";
      ss << PRICE << ": " << price << ", ";
      ss << CURRENCY << ": " << currency << ", ";
      ss << AUTOMATIC << ": " << automatic.toString() << ", ";
      ss << HIDDEN << ": " << hidden.toString() << ", ";
      ss << HIDE_LICENSES << ": " << hideLicenses.toString();

      for (const auto& pair : getProperties()) {
          ss << ", " << pair.first << ": " << pair.second.toString();
      }

      ss << "]";
      return ss.str();
    }
  };

}

#endif // __LICENSE_TEMPLATE_H__
