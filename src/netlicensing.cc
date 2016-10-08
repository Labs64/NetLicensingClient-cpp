#include "netlicensing/netlicensing.h"
#include "netlicensing/service.h"

namespace netlicensing {

  Product ProductService::create(Context& ctx, const Product& product) {
    StandardMapper<Product> productMapper;
    netlicensing::create(ctx, productMapper, product);
    // assert(productMapper.getItems().size() == 1);
    return productMapper.getItems().front();
  }

  Product ProductService::update(Context& ctx, const std::string& productNumber, const Product& product) {
    StandardMapper<Product> productMapper;
    netlicensing::update(ctx, productMapper, productNumber, product);
    // assert(productMapper.getItems().size() == 1);
    return productMapper.getItems().front();
  }

  void ProductService::del(Context& ctx, const std::string& productNumber, bool forceCascade) {
    netlicensing::del<Product>(ctx, productNumber, forceCascade);
  }

  std::list<Product> ProductService::list(Context& ctx, const std::string& filter) {
    StandardMapper<Product> productMapper;
    netlicensing::list(ctx, productMapper, filter);
    return productMapper.getItems();
  }

  //
  // LicenseeService
  //
  Licensee LicenseeService::create(Context& ctx, const Licensee& licensee) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::create(ctx, licenseeMapper, licensee);
    // assert(licenseeMapper.getItems().size() == 1);
    return licenseeMapper.getItems().front();
  }

  Licensee LicenseeService::update(Context& ctx, const std::string& productNumber, const Licensee& licensee) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::update(ctx, licenseeMapper, productNumber, licensee);
    // assert(licenseeMapper.getItems().size() == 1);
    return licenseeMapper.getItems().front();
  }

  void LicenseeService::del(Context& ctx, const std::string& licenseeNumber, bool forceCascade) {
    netlicensing::del<Licensee>(ctx, licenseeNumber, forceCascade);
  }

  std::list<Licensee> LicenseeService::list(Context& ctx, const std::string& filter) {
    StandardMapper<Licensee> licenseeMapper;
    netlicensing::list(ctx, licenseeMapper, filter);
    return licenseeMapper.getItems();
  }

  ValidationResult LicenseeService::validate(Context& ctx, 
      const std::string& licenseeNumber,
      const std::string& productNumber/* = std::string()*/,
      const std::string& licenseeName/* = std::string()*/,
      const parameters_type& validationParameters) {
    std::string endpoint = "licensee/" + escape_string(licenseeNumber) + "/validate";
    parameters_type params;
    if (!productNumber.empty()) params.push_back(std::make_pair("productNumber", escape_string(productNumber)));
    if (!licenseeName.empty()) params.push_back(std::make_pair("licenseeName", escape_string(licenseeName)));

    // Add licensing model specific validation parameters
    for (parameters_type::const_iterator paramIt = validationParameters.begin();
         paramIt != validationParameters.end(); ++paramIt) {
      params.push_back(std::make_pair(escape_string(paramIt->first), escape_string(paramIt->second)));
    }

    long http_code;
    std::string res = ctx.get(endpoint, params, http_code);
    ValidationResult validationResult;
    ValidationResultMapper vrm(validationResult);
    traverse(vrm, res);

    if (http_code != 200) {
      throw RestException(vrm.getInfos(), http_code);
    }

    return validationResult;
  }

}
