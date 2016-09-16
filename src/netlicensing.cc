#include "netlicensing/netlicensing.h"

namespace netlicensing {

  std::list<ValidationResult> ValidationService::validate(Context& ctx, 
    const std::string& licenseeNumber,
    const std::string& productNumber/* = std::string()*/,
    const std::string& licenseeName/* = std::string()*/,
	const parameters_type additionalAttributes) 
  {
      std::string endpoint = "licensee/" + escape_string(licenseeNumber) + "/validate";
      parameters_type params;
      if (!productNumber.empty()) params.push_back(std::make_pair("productNumber", escape_string(productNumber)));
      if (!licenseeName.empty()) params.push_back(std::make_pair("licenseeName", escape_string(licenseeName)));

	  // Add any additional attributes to the params list
	  parameters_type::const_iterator paramIt;
	  for (paramIt = additionalAttributes.begin(); paramIt != additionalAttributes.end(); ++paramIt) 
	  {
		  // Escape pair data and add to the params list
		  params.push_back(std::make_pair(escape_string((*paramIt).first), escape_string((*paramIt).second)));
	  }

      long http_code;
      std::string res = ctx.get(endpoint, params, http_code);
      Mapper<ValidationResult> mp;
      traverse(mp, res);

      if (http_code != 200) {
        throw RestException(mp.info_, http_code);
      }

      return mp.items;
  };

  Product ProductService::create(Context& ctx, const Product& product) {
    return netlicensing::create(ctx, product);
  }

  Product ProductService::update(Context& ctx, const std::string& productNumber, const Product& product) {
    return netlicensing::update(ctx, productNumber, product);
  }

  void ProductService::del(Context& ctx, const std::string& productNumber, bool forceCascade) {
    netlicensing::del<Product>(ctx, productNumber, forceCascade);
  }

  std::list<Product> ProductService::list(Context& ctx, const std::string& filter) {
    return netlicensing::list<Product>(ctx, filter);
  }

  //
  // LicenseeService
  //
  Licensee LicenseeService::create(Context& ctx, const Licensee& licensee) {
	  return netlicensing::create(ctx, licensee);
  }

  Licensee LicenseeService::update(Context& ctx, const std::string& productNumber, const Licensee& licensee) {
	  return netlicensing::update(ctx, productNumber, licensee);
  }

  void LicenseeService::del(Context& ctx, const std::string& licenseeNumber, bool forceCascade) {
	  netlicensing::del<Licensee>(ctx, licenseeNumber, forceCascade);
  }

  std::list<Licensee> LicenseeService::list(Context& ctx, const std::string& filter) {
	  return netlicensing::list<Licensee>(ctx, filter);
  }
}
