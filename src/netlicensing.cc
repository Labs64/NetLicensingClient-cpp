#include "netlicensing/netlicensing.h"
#include "netlicensing/service.h"
#include "netlicensing/validation_parameters.h"

namespace netlicensing {
  /**
  * C++ representation of the Product Service. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Product+Services
  */

  /**
  * Creates new product object with given properties. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Product+Services#ProductServices-Createproduct
  */
  Product ProductService::create(Context& ctx, const Product& product) {
    StandardMapper<Product> productMapper;
    netlicensing::create(ctx, productMapper, product);
    // assert(productMapper.getItems().size() == 1);
    return productMapper.getItems().front();
  }

  /**
  * Updates product properties. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Product+Services#ProductServices-Updateproduct
  */
  Product ProductService::update(Context& ctx, const std::string& productNumber, const Product& product) {
    StandardMapper<Product> productMapper;
    netlicensing::update(ctx, productMapper, productNumber, product);
    // assert(productMapper.getItems().size() == 1);
    return productMapper.getItems().front();
  }

  /**
  * Deletes product. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Product+Services#ProductServices-Deleteproduct
  */
  void ProductService::del(Context& ctx, const std::string& productNumber, bool forceCascade) {
    netlicensing::del<Product>(ctx, productNumber, forceCascade);
  }

  /**
  * Returns all products of a vendor. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Product+Services#ProductServices-Productslist
  */
  std::list<Product> ProductService::list(Context& ctx, const std::string& filter) {
    StandardMapper<Product> productMapper;
    netlicensing::list(ctx, productMapper, filter);
    return productMapper.getItems();
  }

  /**
  * C++ representation of the Licensee Service. See NetLicensingAPI JavaDoc for details:
  * http://netlicensing.labs64.com/javadoc/v2/com/labs64/netlicensing/core/service/LicenseeService.html
  */

  /**
  * Creates new licensee object with given properties. See NetLicensingAPI JavaDoc for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Createlicensee
  */
  Licensee LicenseeService::create(Context& ctx, const Licensee& licensee) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::create(ctx, licenseeMapper, licensee);
    // assert(licenseeMapper.getItems().size() == 1);
    return licenseeMapper.getItems().front();
  }

  /**
  * Updates licensee properties. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Updatelicensee
  */
  Licensee LicenseeService::update(Context& ctx, const std::string& productNumber, const Licensee& licensee) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::update(ctx, licenseeMapper, productNumber, licensee);
    // assert(licenseeMapper.getItems().size() == 1);
    return licenseeMapper.getItems().front();
  }

  /**
  * Deletes licensee. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Deletelicensee
  */
  void LicenseeService::del(Context& ctx, const std::string& licenseeNumber, bool forceCascade) {
    netlicensing::del<Licensee>(ctx, licenseeNumber, forceCascade);
  }

  /**
  * Returns all licensees of a vendor. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Licenseeslist
  */
  std::list<Licensee> LicenseeService::list(Context& ctx, const std::string& filter) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::list(ctx, licenseeMapper, filter);
    return licenseeMapper.getItems();
  }

  /**
  * Validates active licenses of the licensee. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Validatelicensee
  */
  ValidationResult LicenseeService::validate(Context& ctx,
    const std::string& licenseeNumber,
    const std::string& productNumber/* = std::string()*/,
    const std::string& licenseeName/* = std::string()*/,
    const parameters_type& validationParameters) {

    ValidationParameters vParams = ValidationParameters();
    if (!productNumber.empty()) {
      vParams.setProductNumber(productNumber);
    }
    if (!licenseeName.empty()) {
      vParams.setLicenseeName(licenseeName);
    }

    for (parameters_type::const_iterator paramIt = validationParameters.begin();
         paramIt != validationParameters.end(); ++paramIt) {

      if (escape_string(paramIt->first) == "licenseeSecret") {
        vParams.setLicenseeSecret(escape_string(paramIt->second));
      } else {
        vParams.setCustomParameter(escape_string(paramIt->first), escape_string(paramIt->second));
      }
    }

    return LicenseeService::validate(ctx, licenseeNumber, vParams);
  }

  /**
  * Validates active licenses of the licensee. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Validatelicensee
  */
  ValidationResult LicenseeService::validate(Context& ctx, 
    const std::string& licenseeNumber,
    const ValidationParameters& validationParameters) {
      std::string endpoint = "licensee/" + escape_string(licenseeNumber) + "/validate";
      parameters_type params;

      if (!escape_string(validationParameters.getProductNumber()).empty()) {
        params.push_back(std::make_pair("productNumber", escape_string(validationParameters.getProductNumber())));
      }
      if (!escape_string(validationParameters.getLicenseeName()).empty()) {
        params.push_back(std::make_pair("licenseeName", escape_string(validationParameters.getLicenseeName())));
      }
      if (!escape_string(validationParameters.getLicenseeSecret()).empty()) {
        params.push_back(std::make_pair("licenseeSecret", escape_string(validationParameters.getLicenseeSecret())));
      }

      int paramIt = 0;
      for(auto const &ent1 : validationParameters.getParameters()) {
        auto const &productModuleNumber = ent1.first;
        auto const &productModuleParameters = ent1.second;
        params.push_back(std::make_pair("productModuleNumber" + std::to_string(paramIt), escape_string(productModuleNumber)));

        for(auto const &ent2 : productModuleParameters) {
          auto const &inner_key   = ent2.first;
          auto const &inner_value = ent2.second;
          params.push_back(std::make_pair(escape_string(inner_key) + std::to_string(paramIt), escape_string(inner_value)));
        }
        paramIt++;
      }

      // Add licensing model specific validation parameters
      for(auto const &ent3 : validationParameters.getCustomParameters()) {
        params.push_back(std::make_pair(escape_string(ent3.first), escape_string(ent3.second)));
      }

      long http_code;
      std::string res = ctx.post(endpoint, params, http_code);
      ValidationResult validationResult;
      ValidationResultMapper vrm(validationResult);
      traverse(vrm, res);

      //convert ttl in time_t
      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse(res.c_str(), root);
      if (parsingSuccessful) {
        Json::FastWriter fastWriter;
        //ttl returns with new line character ("\n") is appended at the end of the string and "\" at the begin of string.
        std::string ttl = fastWriter.write(root["ttl"]);

        struct tm tm = {0};
        tm.tm_year = atoi(ttl.substr(1,4).c_str()) - 1900; /* years since 1900 */
        tm.tm_mon = atoi(ttl.substr(6, 2).c_str()) - 1;
        tm.tm_mday = atoi(ttl.substr(9, 2).c_str());
        tm.tm_hour = atoi(ttl.substr(12, 2).c_str());
        tm.tm_min = atoi(ttl.substr(15, 2).c_str());
        tm.tm_sec = atoi(ttl.substr(18, 2).c_str());

        time_t rawtime = mktime(&tm);
        validationResult.setTtl(rawtime);
      }

      if (http_code != 200) {
        throw RestException(vrm.getInfos(), http_code);
      }

      return validationResult;
  }

  /**
  * Transfer licenses between licensees.:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Transferlicensee
  */
  void LicenseeService::transfer(Context& ctx, const std::string& licenseeNumber, const std::string& sourceLicenseeNumber) {
    std::string endpoint = "licensee/" + escape_string(licenseeNumber) + "/transfer";
    parameters_type params;
    if (!sourceLicenseeNumber.empty()) params.push_back(std::make_pair("sourceLicenseeNumber", escape_string(sourceLicenseeNumber)));

    long http_code;
    std::string res = ctx.post(endpoint, params, http_code);
  }
}
