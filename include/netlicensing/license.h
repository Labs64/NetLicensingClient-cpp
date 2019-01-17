#ifndef __LICENSE_H__
#define __LICENSE_H__

#include <list>

#include "netlicensing/entity.h"

namespace netlicensing {

  class License : public BaseEntity {
  private:
    String_t name_i;
    String_t price_i;//TODO(AY): change type to Double ?
    String_t currency_i;//TODO(AY): change type to Currency
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

    String_t toString() const {
      std::string name(this->getName());
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());
      std::string price(this->getPrice());
      std::string currency(this->getCurrency());
      Boolean_t hidden(this->getHidden());
      std::string licenseeNumber(this->getLicenseeNumber());
      std::string licenseTemplateNumber(this->getLicenseTemplateNumber());

      std::stringstream ss;
      ss << "License [";
      ss << "name: ";
      ss << name;
      ss << ", ";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << ", ";
      ss << "price: ";
      ss << price;
      ss << ", ";
      ss << "currency: ";
      ss << currency;
      ss << ", ";
      ss << "hidden: ";
      ss << hidden.toString();
      ss << ", ";
      ss << "licenseeNumber: ";
      ss << licenseeNumber;
      ss << ", ";
      ss << "licenseTemplateNumber: ";
      ss << licenseTemplateNumber;
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __LICENSE_H__
