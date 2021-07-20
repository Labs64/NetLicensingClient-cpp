#include "netlicensing/constants.h"
#include "netlicensing/netlicensing.h"
#include "netlicensing/service.h"
#include "netlicensing/validation_parameters.h"
#include <time.h>

namespace netlicensing {
  /**
  * C++ representation of the Product Service. See NetLicensingAPI for details:
  * https://netlicensing.io/wiki/product-services
  */

  /**
  * Creates new product object with given properties. See NetLicensingAPI for details:
  * https://netlicensing.io/wiki/product-services#create-product
  */
  Product ProductService::create(Context& ctx, const Product& product) {
    StandardMapper<Product> productMapper;
    netlicensing::create(ctx, productMapper, product);
    return productMapper.getItems().front();
  }

  /**
   * Get product object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Services#ProductServices-Getproduct
   */
  Product ProductService::get(Context& ctx, const std::string& productNumber) {
    StandardMapper<Product> productMapper;
    netlicensing::get(ctx, productMapper, productNumber);
    return productMapper.getItems().front();
  }

  /**
  * Updates product properties. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Product+Services#ProductServices-Updateproduct
  */
  Product ProductService::update(Context& ctx, const std::string& productNumber, const Product& product) {
    StandardMapper<Product> productMapper;
    netlicensing::update(ctx, productMapper, productNumber, product);
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
   * C++ representation of the Product Module Service. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Module+Services
   */

  /**
   * Creates new product module object with given properties. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Module+Services#ProductModuleServices-Createproductmodule
   */
  ProductModule ProductModuleService::create(Context& ctx, const ProductModule& productModule) {
    StandardMapper<ProductModule> productModuleMapper;
    netlicensing::create(ctx, productModuleMapper, productModule);
    return productModuleMapper.getItems().front();
  }

  /**
   * Get product module object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Module+Services#ProductModuleServices-Getproductmodule
   */
  ProductModule ProductModuleService::get(Context& ctx, const std::string& productModuleNumber) {
    StandardMapper<ProductModule> productModuleMapper;
    netlicensing::get(ctx, productModuleMapper, productModuleNumber);
    return productModuleMapper.getItems().front();
  }

  /**
   * Returns all product modules of a vendor. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Module+Services#ProductModuleServices-Productmoduleslist
   */
  std::list<ProductModule> ProductModuleService::list(Context& ctx, const std::string& filter) {
    StandardMapper<ProductModule> productModuleMapper;
    netlicensing::list(ctx, productModuleMapper, filter);
    return productModuleMapper.getItems();
  }

  /**
   * Updates product module properties. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Module+Services#ProductModuleServices-Updateproductmodule
   */
  ProductModule ProductModuleService::update(Context& ctx, const std::string& productModuleNumber, const ProductModule& productModule) {
    StandardMapper<ProductModule> productModuleMapper;
    netlicensing::update(ctx, productModuleMapper, productModuleNumber, productModule);
    return productModuleMapper.getItems().front();
  }

  /**
   * Deletes product module. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Product+Module+Services#ProductModuleServices-Deleteproductmodule
   */
  void ProductModuleService::del(Context& ctx, const std::string& productModuleNumber, bool forceCascade) {
    netlicensing::del<ProductModule>(ctx, productModuleNumber, forceCascade);
  }

  /**
   * C++ representation of the License Template Service. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Template+Services
   */

  /**
   * Creates new license template object with given properties. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Template+Services#LicenseTemplateServices-Createlicensetemplate
   */
  LicenseTemplate LicenseTemplateService::create(Context& ctx, const LicenseTemplate& licenseTemplate) {
    StandardMapper<LicenseTemplate> licenseTemplateMapper;
    netlicensing::create(ctx, licenseTemplateMapper, licenseTemplate);
    return licenseTemplateMapper.getItems().front();
  }

  /**
   * Get license template object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Template+Services#LicenseTemplateServices-Getlicensetemplate
   */
  LicenseTemplate LicenseTemplateService::get(Context& ctx, const std::string& licenseTemplateNumber) {
    StandardMapper<LicenseTemplate> licenseTemplateMapper;
    netlicensing::get(ctx, licenseTemplateMapper, licenseTemplateNumber);
    return licenseTemplateMapper.getItems().front();
  }

  /**
   * Returns all license templates of a vendor. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Template+Services#LicenseTemplateServices-Licensetemplateslist
   */
  std::list<LicenseTemplate> LicenseTemplateService::list(Context& ctx, const std::string& filter) {
    StandardMapper<LicenseTemplate> licenseTemplateMapper;
    netlicensing::list(ctx, licenseTemplateMapper, filter);
    return licenseTemplateMapper.getItems();
  }

  /**
   * Updates license template properties. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Template+Services#LicenseTemplateServices-Updatelicensetemplate
   */
  LicenseTemplate LicenseTemplateService::update(Context& ctx, const std::string& licenseTemplateNumber, const LicenseTemplate& licenseTemplate) {
    StandardMapper<LicenseTemplate> licenseTemplateMapper;
    netlicensing::update(ctx, licenseTemplateMapper, licenseTemplateNumber, licenseTemplate);
    return licenseTemplateMapper.getItems().front();
  }

  /**
   * Deletes license template. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Template+Services#LicenseTemplateServices-Deletelicensetemplate
   */
  void LicenseTemplateService::del(Context& ctx, const std::string& licenseTemplateNumber, bool forceCascade) {
    netlicensing::del<LicenseTemplate>(ctx, licenseTemplateNumber, forceCascade);
  }

  /**
  * C++ representation of the Licensee Service. See NetLicensingAPI JavaDoc for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services
  */

  /**
  * Creates new licensee object with given properties. See NetLicensingAPI JavaDoc for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Createlicensee
  */
  Licensee LicenseeService::create(Context& ctx, const Licensee& licensee) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::create(ctx, licenseeMapper, licensee);
    return licenseeMapper.getItems().front();
  }

  /**
   * Get licensee object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Getlicensee
   */
  Licensee LicenseeService::get(Context& ctx, const std::string& licenseeNumber) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::get(ctx, licenseeMapper, licenseeNumber);
    return licenseeMapper.getItems().front();
  }

  /**
  * Updates licensee properties. See NetLicensingAPI for details:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Updatelicensee
  */
  Licensee LicenseeService::update(Context& ctx, const std::string& number, const Licensee& licensee) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::update(ctx, licenseeMapper, number, licensee);
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
   * https://netlicensing.io/wiki/licensee-services#validate-licensee
   */
  ValidationResult LicenseeService::validate(Context& ctx,
    const std::string& licenseeNumber,
    const std::string& productNumber/* = std::string()*/,
    const std::string& licenseeName/* = std::string()*/,
    const parameters_type& validationParameters) {

      std::string endpoint = std::string(LICENSEE_ENDPOINT_PATH) + "/" + escape_string(licenseeNumber) + "/" + ENDPOINT_PATH_VALIDATE;
      parameters_type params;
      if (!productNumber.empty()) params.push_back(std::make_pair(PRODUCT_NUMBER, escape_string(productNumber)));
      if (!licenseeName.empty()) params.push_back(std::make_pair(PROP_LICENSEE_NAME, escape_string(licenseeName)));

      // Add licensing model specific validation parameters
      for (parameters_type::const_iterator paramIt = validationParameters.begin();
           paramIt != validationParameters.end(); ++paramIt) {
        params.push_back(std::make_pair(escape_string(paramIt->first), escape_string(paramIt->second)));
      }

      long http_code;
      std::string res = ctx.post(endpoint, params, http_code);
      ValidationResult validationResult;
      ValidationResultMapper vrm(validationResult);
      traverse(vrm, res);

      if (http_code != 200) {
        throw RestException(vrm.getInfos(), http_code);
      }

      return validationResult;
  }

  /**
  * Validates active licenses of the licensee.
  * In the case of multiple product modules validation, required parameters indexes will be added automatically.
  * See NetLicensingAPI for details: https://netlicensing.io/wiki/licensee-services#validate-licensee
  */
  ValidationResult LicenseeService::validate(Context& ctx, 
    const std::string& licenseeNumber,
    const ValidationParameters& validationParameters) {
      std::string endpoint = std::string(LICENSEE_ENDPOINT_PATH) + "/" + escape_string(licenseeNumber) + "/" + ENDPOINT_PATH_VALIDATE;
      parameters_type params;

      if (!escape_string(validationParameters.getProductNumber()).empty()) {
        params.push_back(std::make_pair(PRODUCT_NUMBER, escape_string(validationParameters.getProductNumber())));
      }
      if (!escape_string(validationParameters.getLicenseeName()).empty()) {
        params.push_back(std::make_pair(PROP_LICENSEE_NAME, escape_string(validationParameters.getLicenseeName())));
      }
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
      if (!escape_string(validationParameters.getLicenseeSecret()).empty()) {
        params.push_back(std::make_pair(PROP_LICENSEE_SECRET, escape_string(validationParameters.getLicenseeSecret())));
      }
#ifdef __clang__
#pragma clang diagnostic pop
#endif

      int paramIt = 0;
      for(auto const &ent1 : validationParameters.getParameters()) {
        auto const &productModuleNumber = ent1.first;
        auto const &productModuleParameters = ent1.second;
        params.push_back(std::make_pair(PRODUCT_MODULE_NUMBER + std::to_string(paramIt), escape_string(productModuleNumber)));

        for(auto const &ent2 : productModuleParameters) {
          auto const &inner_key   = ent2.first;
          auto const &inner_value = ent2.second;
          params.push_back(std::make_pair(escape_string(inner_key) + std::to_string(paramIt), escape_string(inner_value)));
        }
        paramIt++;
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
        struct tm ttlTime;
        std::size_t isNull = ttl.find("null");
        if (isNull==std::string::npos) {
          ttlTime.tm_year = atoi(ttl.substr(1,4).c_str()) - 1900; /* years since 1900 */
          ttlTime.tm_mon = atoi(ttl.substr(6, 2).c_str()) - 1;
          ttlTime.tm_mday = atoi(ttl.substr(9, 2).c_str());
          ttlTime.tm_hour = atoi(ttl.substr(12, 2).c_str());
          ttlTime.tm_min = atoi(ttl.substr(15, 2).c_str());
          ttlTime.tm_sec = atoi(ttl.substr(18, 2).c_str());
        }
        time_t rawtime = mktime(&ttlTime);
        validationResult.setTtl(rawtime);
      }

      if (http_code != 200) {
        throw RestException(vrm.getInfos(), http_code);
      }

      return validationResult;
  }

  /**
  * Transfer licenses between licensees.:
  * https://www.labs64.de/confluence/display/NLICPUB/Licensee+Services#LicenseeServices-Transferlicenses
  */
  void LicenseeService::transfer(Context& ctx, const std::string& licenseeNumber, const std::string& sourceLicenseeNumber) {
    std::string endpoint = "licensee/" + escape_string(licenseeNumber) + "/" + ENDPOINT_PATH_TRANSFER;
    parameters_type params;
    if (!sourceLicenseeNumber.empty()) params.push_back(std::make_pair(SOURCE_LICENSEE_NUMBER, escape_string(sourceLicenseeNumber)));

    long http_code;
    std::string res = ctx.post(endpoint, params, http_code);
  }

  /**
   * C++ representation of the License. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Services
   */

  /**
   * Creates new license object with given properties. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Services#LicenseServices-Createlicense
   */
  License LicenseService::create(Context& ctx, const License& license) {
    StandardMapper<License> licenseMapper;
    netlicensing::create(ctx, licenseMapper, license);
    return licenseMapper.getItems().front();
  }

  /**
   * Get license object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Services#LicenseServices-Getlicense
   */
  License LicenseService::get(Context& ctx, const std::string& licenseNumber) {
    StandardMapper<License> licenseMapper;
    netlicensing::get(ctx, licenseMapper, licenseNumber);
    return licenseMapper.getItems().front();
  }

  /**
   * Updates license properties. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Services#LicenseServices-Updatelicense
   */
  License LicenseService::update(Context& ctx, const std::string& number, const License& license) {
    StandardMapper<License> licenseMapper;
    netlicensing::update(ctx, licenseMapper, number, license);
    return licenseMapper.getItems().front();
  }

  /**
   * Deletes license. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Services#LicenseServices-Deletelicense
   */
  void LicenseService::del(Context& ctx, const std::string& licenseNumber, bool forceCascade) {
    netlicensing::del<License>(ctx, licenseNumber, forceCascade);
  }

  /**
   * Returns all licenses of a vendor. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/License+Services#LicenseServices-Licenseslist
   */
  std::list<License> LicenseService::list(Context& ctx, const std::string& filter) {
    StandardMapper<License> licenseMapper;
    netlicensing::list(ctx, licenseMapper, filter);
    return licenseMapper.getItems();
  }

  /**
   * C++ representation of the Payment Method. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Payment+Method+Services
   */

  /**
   * Get payment method object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Payment+Method+Services#PaymentMethodServices-Getpaymentmethod
   */
  PaymentMethod PaymentMethodService::get(Context& ctx, const std::string& number) {
    StandardMapper<PaymentMethod> paymentMethodMapper;
    netlicensing::get(ctx, paymentMethodMapper, number);
    return paymentMethodMapper.getItems().front();
  }

  /**
   * Updates payment method. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Payment+Method+Services#PaymentMethodServices-Updatepaymentmethod
   */
  PaymentMethod PaymentMethodService::update(Context& ctx, const std::string& number, const PaymentMethod& paymentMethod) {
    StandardMapper<PaymentMethod> paymentMethodMapper;
    netlicensing::update(ctx, paymentMethodMapper, number, paymentMethod);
    return paymentMethodMapper.getItems().front();
  }

  /**
   * Returns all payment methods. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Payment+Method+Services#PaymentMethodServices-Paymentmethodslist
   */
  std::list<PaymentMethod> PaymentMethodService::list(Context& ctx, const std::string& filter) {
    StandardMapper<PaymentMethod> paymentMethodMapper;
    netlicensing::list(ctx, paymentMethodMapper, filter);
    return paymentMethodMapper.getItems();
  }

  /**
   * C++ representation of the Token. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Token+Services
   */

  /**
   * Creates new token object with given properties. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Token+Services#TokenServices-Createtoken
   */
  Token TokenService::create(Context& ctx, const Token& token) {
    StandardMapper<Token> tokenMapper;
    netlicensing::create(ctx, tokenMapper, token);
    return tokenMapper.getItems().front();
  }

  /**
   * Get token object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Token+Services#TokenServices-Gettoken
   */
  Token TokenService::get(Context& ctx, const std::string& number) {
    StandardMapper<Token> tokenMapper;
    netlicensing::get(ctx, tokenMapper, number);
    return tokenMapper.getItems().front();
  }

  /**
   * Deletes token. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Token+Services#TokenServices-Deletetoken
   */
  void TokenService::del(Context& ctx, const std::string& number, bool forceCascade) {
    netlicensing::del<Token>(ctx, number, forceCascade);
  }

  /**
   * Returns all tokens. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Token+Services#TokenServices-Tokenslist
   */
  std::list<Token> TokenService::list(Context& ctx, const std::string& filter) {
    StandardMapper<Token> tokenMapper;
    netlicensing::list(ctx, tokenMapper, filter);
    return tokenMapper.getItems();
  }

  /**
   * C++ representation of the Transaction. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Transaction+Services
   */

  /**
   * Creates new transaction object with given properties. See NetLicensingAPI JavaDoc for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Transaction+Services#TransactionServices-Createtransaction
   */
  Transaction TransactionService::create(Context& ctx, const Transaction& transaction) {
    StandardMapper<Transaction> transactionMapper;
    netlicensing::create(ctx, transactionMapper, transaction);
    return transactionMapper.getItems().front();
  }

  /**
   * Updates transaction. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Transaction+Services#TransactionServices-Updatetransaction
   */
  Transaction TransactionService::update(Context& ctx, const std::string& number, const Transaction& transaction) {
    StandardMapper<Transaction> transactionMapper;
    netlicensing::update(ctx, transactionMapper, number, transaction);
    return transactionMapper.getItems().front();
  }

  /**
   * Get transaction object with. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Transaction+Services#TransactionServices-Gettransaction
   */
  Transaction TransactionService::get(Context& ctx, const std::string& number) {
    StandardMapper<Transaction> transactionMapper;
    netlicensing::get(ctx, transactionMapper, number);
    return transactionMapper.getItems().front();
  }

  /**
   * Returns all transaction. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Transaction+Services#TransactionServices-Transactionslist
   */
  std::list<Transaction> TransactionService::list(Context& ctx, const std::string& filter) {
    StandardMapper<Transaction> transactionMapper;
    netlicensing::list(ctx, transactionMapper, filter);
    return transactionMapper.getItems();
  }

  /**
   * C++ representation of the Utility Service. See NetLicensingAPI JavaDoc for details:
   * https://go.netlicensing.io/javadoc/v2/com/labs64/netlicensing/service/UtilityService.html
   */

  /**
   * Returns all countries. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Utility+Services
   */
  std::list<Country> UtilityService::listCountries(Context& ctx) {
    StandardMapper<Country> countryMapper;
    netlicensing::list(ctx, countryMapper, "");
    return countryMapper.getItems();
  }

  /**
   * Returns all licensing models. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Utility+Services#UtilityServices-LicensingModelslist
   */
  std::list<LicensingModel> UtilityService::listLicensingModels(Context& ctx) {
    StandardMapper<LicensingModel> licensingModelsMapper;
    netlicensing::list(ctx, licensingModelsMapper, "");
    return licensingModelsMapper.getItems();
  }

  /**
   * Returns all license types. See NetLicensingAPI for details:
   * https://www.labs64.de/confluence/display/NLICPUB/Utility+Services#UtilityServices-LicenseTypeslist
   */
  std::list<LicenseType> UtilityService::listLicenseTypes(Context& ctx) {
    StandardMapper<LicenseType> licenseTypeMapper;
    netlicensing::list(ctx, licenseTypeMapper, "");
    return licenseTypeMapper.getItems();
  }
}
