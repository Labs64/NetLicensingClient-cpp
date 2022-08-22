#ifndef __VALIDATION_PARAMETERS_H__
#define __VALIDATION_PARAMETERS_H__

#include <map>
#include <sstream>
#include <string>

#include "netlicensing/datatypes.h"

namespace netlicensing {

  class ValidationParameters {

  private:
    String_t productNumber_i;
    String_t licenseeName_i;
    String_t licenseeSecret_i;
    std::map<std::string, std::string> licenseeParameters_i;
    std::map<std::string, std::map<std::string, std::string>> parameters_i;

  public:
    /**
    * Sets the target product
    *
    * @param productNumber
    *            optional productNumber, must be provided in case licensee auto-create is enabled
    */
    void setProductNumber(const String_t& productNumber) {
      productNumber_i = productNumber;
    }

    const String_t& getProductNumber() const {
      return productNumber_i;
    }

    const std::map<std::string, std::string>& getLicenseeProperties() const {
        return licenseeParameters_i;
    }

    void setLicenseeProperty(const String_t& key, const String_t& value) {
        licenseeParameters_i[key] = value;
    }

    /**
    * Sets the name for the new licensee
    *
    * @param licenseeName
    *            optional human-readable licensee name in case licensee will be auto-created. This parameter must not
    *            be the name, but can be used to store any other useful string information with new licensees, up to
    *            1000 characters.
    */
    void setLicenseeName(const String_t& licenseeName) {
        licenseeParameters_i[PROP_LICENSEE_NAME] = licenseeName;
    }

    const String_t& getLicenseeName() const {
      return licenseeParameters_i[PROP_LICENSEE_NAME];
    }

    /**
    * Sets the licensee secret
    *
    * @param licenseeSecret
    *            licensee secret stored on the client side. Refer to Licensee Secret documentation for details.
    */
    [[deprecated("use NodeLocked licensing model instead")]]
    void setLicenseeSecret(const String_t& licenseeSecret) {
        licenseeParameters_i[PROP_LICENSEE_SECRET] = licenseeSecret;
    }

    [[deprecated("use NodeLocked licensing model instead")]]
    const String_t& getLicenseeSecret() const {
      return licenseeParameters_i[PROP_LICENSEE_SECRET];
    }

    const std::map<std::string, std::map<std::string, std::string>>& getParameters() const {
      return parameters_i;
    }

    void setProductModuleValidationParameters(const String_t& productModuleNumber, const String_t& productModuleKey, const String_t& productModuleValue) {
      parameters_i[productModuleNumber][productModuleKey] = productModuleValue;
    }
  };
}

#endif //__VALIDATION_PARAMETERS_H__
