#include <iostream>
#include "netlicensing/context.h"
#include "netlicensing/service.h"
#include "netlicensing/exception.h"
#include "netlicensing/product.h"
#include "json/json.h"

int main(int argc, char* argv[]) {
  using netlicensing::Product;
  std::string license_number = "I2C3VN7NA-DEMO";
  if (argc > 1) {
    license_number = argv[1];
  }
  std::cout << "Hello, this is NetLicensing demo client\n";

  std::cout << "Product endpoint " << netlicensing::endpoint<Product>() << std::endl;

  // check context direct call 
  std::list<std::pair<std::string, std::string> > params;
  params.push_back(std::make_pair("licenseeNumber", "1"));
  params.push_back(std::make_pair("licenseTemplateNumber", "1"));
  params.push_back(std::make_pair("active", "true"));
  params.push_back(std::make_pair("number", "1"));
  params.push_back(std::make_pair("name", "lic"));

  using netlicensing::Context;
  try {
    Context ctx;
    ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
    ctx.set_username("demo");
    ctx.set_password("demo");
    long http_code;
    std::string res = ctx.post("license", params, http_code);
    std::cout << "license check answer: " << res << std::endl;

    //std::string lres = ctx.get("licensetemplate", Context::parameters_type());
    //std::cout << "licensee list " << lres << std::endl;

    //std::string ldel = ctx.del("licensetemplate/E00101-DEMO", Context::parameters_type());
    //std::cout << "delete license " << ldel << std::endl;
    if (!license_number.empty()) {
      std::cout << "start validation for " << license_number << std::endl;
      std::list<netlicensing::ValidationResult> vres = netlicensing::validate(ctx, license_number);
      std::cout << "got validation results: " << vres.size() << std::endl;
      for (auto val_res : vres) {
        std::cout << val_res.to_string() << std::endl;
      }
    }
  }
  catch (const netlicensing::RestException& e) {
    std::cerr << e.what() << " code " << e.http_code() << std::endl;
    for (auto det : e.get_details()) {
      std::cerr << det.to_string() << std::endl;
    }
    return 2;
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }

  return 0;
}
