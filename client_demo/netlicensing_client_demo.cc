#include <iostream>
#include <random>  
#include <ctime> 
#include <sstream>
#include "netlicensing/netlicensing.h"

int main(int argc, char* argv[]) {
  using netlicensing::Product;
  std::string licensee_number = "I2C3VN7NA-DEMO";
  if (argc > 1) {
    licensee_number = argv[1];
  }

  std::mt19937 gen;
  gen.seed(time(0));
  std::stringstream ss;
  ss << "P" << gen();
  std::string productNumber = ss.str();

  std::cout << "Hello, this is NetLicensing demo client\n";
  std::cout << "Product endpoint " << netlicensing::endpoint<Product>() << std::endl;
  std::cout << "Product test number " << productNumber << std::endl;

  using netlicensing::Context;
  try {
    Context ctx;
    ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
    ctx.set_username("demo");
    ctx.set_password("demo");

    // product section
    netlicensing::Product p;
    p.setName("Test name");
    p.setNumber(productNumber);
    netlicensing::Product newp = netlicensing::ProductService::create(ctx, p);

    newp.setName("Updated name");
    netlicensing::Product newp2 = netlicensing::ProductService::update(ctx, newp.getNumber(), newp);

    std::list<netlicensing::Product> products = netlicensing::ProductService::list(ctx, "");
    std::cout << "before delete products count " << products.size() << std::endl;

    netlicensing::ProductService::del(ctx, newp2.getNumber(), false);

    products = netlicensing::ProductService::list(ctx, "");
    std::cout << "after delete products count " << products.size() << std::endl;
    
    if (!licensee_number.empty()) {
      std::cout << "start validation for " << licensee_number << std::endl;
      std::list<netlicensing::ValidationResult> vres = netlicensing::ValidationService::validate(ctx, licensee_number);
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
