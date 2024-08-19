#ifndef __BUNDLE_H__
#define __BUNDLE_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"


namespace netlicensing {

    class Bundle : public BaseEntity {
    private:
        String_t name_i;
        String_t description_i;
        FixedPoint price_i = FixedPoint(0);
        Currency currency_i;
        std::list<String_t> licenseTemplateNumbers_i;


    public:
        Bundle() : name_i(), description_i(), price_i(), currency_i(), licenseTemplateNumbers_i() { }

        void setName(const String_t& name) {
            name_i = name;
        }

        const String_t& getName() const {
            return name_i;
        }

        void setDescription(const String_t& description) {
            description_i = description;
        }

        const String_t& getDescription() const {
            return description_i;
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

        void setLicenseTemplateNumbers(std::list<String_t>& licenseTemplateNumbers) {
            licenseTemplateNumbers_i = licenseTemplateNumbers;
        }

        std::list<String_t>& getLicenseTemplateNumbers() {
            return licenseTemplateNumbers_i;
        }

        void addLicenseTemplateNumber(const String_t& licenseTemplateNumber) {
            licenseTemplateNumbers_i.push_back(licenseTemplateNumber);
        }

        std::string toString() const {
            std::string number(getNumber());
            Boolean_t active(getActive());
            std::string name(getName());
            std::string description(getDescription());
            std::string price(getPrice().toString());
            std::string currency(currencyToString(getCurrency()));

            std::stringstream ss;
            ss << "Bundle [";
            ss << NUMBER << ": " << number << ", ";
            ss << ACTIVE << ": " << active << ", ";
            ss << NAME << ": " << name << ", ";
            ss << DESCRIPTION << ": " << description << ", ";
            ss << PRICE << ": " << price << ", ";
            ss << CURRENCY << ": " << currency << ", ";
            ss << LICENSE_TEMPLATE_NUMBERS << ": " << join(licenseTemplateNumbers_i, ",");

            for (const auto& pair : getProperties()) {
                ss << ", " << pair.first << ": " << pair.second.toString();
            }

            ss << "]";
            return ss.str();
        }

    };

}

#endif // __BUNDLE_H__