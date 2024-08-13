#ifndef __LICENSE_H__
#define __LICENSE_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"
#include "netlicensing/datatypes.h"

namespace netlicensing {

  class License : public BaseEntity {
  private:
    String_t name_i;
    FixedPoint price_i = FixedPoint(0);
    Currency currency_i;
    Boolean_t hidden_i = false;
    String_t licenseeNumber_i;
    String_t licenseTemplateNumber_i;

  public:
    License() : name_i(), price_i(), currency_i(),
    hidden_i(), licenseeNumber_i(), licenseTemplateNumber_i() { }

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
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

    void setHidden(const Boolean_t hidden) {
      hidden_i = hidden;
    }

    const Boolean_t getHidden() const {
      return hidden_i;
    }

    void setLicenseeNumber(const String_t& licenseeNumber) {
      licenseeNumber_i = licenseeNumber;
    }

    const String_t& getLicenseeNumber() const {
      return licenseeNumber_i;
    }

    void setLicenseTemplateNumber(const String_t& licenseTemplateNumber) {
      licenseTemplateNumber_i = licenseTemplateNumber;
    }

    const String_t& getLicenseTemplateNumber() const {
      return licenseTemplateNumber_i;
    }

    std::string toString() const {
      std::string name(getName());
      std::string number(getNumber());
      Boolean_t active(getActive());
      std::string price(getPrice().toString());
      std::string currency(currencyToString(getCurrency()));
      Boolean_t hidden(getHidden());
      std::string licenseeNumber(getLicenseeNumber());
      std::string licenseTemplateNumber(getLicenseTemplateNumber());

      std::stringstream ss;
      ss << "License [";
      ss << NAME << ": " << name << ", ";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString() << ", ";
      ss << PRICE << ": " << price << ", ";
      ss << CURRENCY << ": " << currency << ", ";
      ss << HIDDEN << ": " << hidden.toString() << ", ";
      ss << LICENSEE_NUMBER << ": " << licenseeNumber << ", ";
      ss << LICENSE_TEMPLATE_NUMBER << ": " << licenseTemplateNumber;

      for (const auto& pair : getProperties()) {
          ss << ", " << pair.first << ": " << pair.second.toString();
      }

      ss << "]";
      return ss.str();
    }
  };

}

#endif // __LICENSE_H__
