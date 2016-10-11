#include <iostream>
#include <random>  
#include <ctime> 
#include <sstream>
#include "netlicensing/netlicensing.h"
#include "netlicensing/constants.h"

int main(int argc, char* argv[]) {
  using namespace netlicensing;

  std::string licensee_number = "IR2Q7A5P3";
  if (argc > 1) {
    licensee_number = argv[1];
  }

  std::mt19937 gen;
  gen.seed(time(0));
  std::stringstream ss;
  ss << "P" << gen();
  std::string productNumber = ss.str();

  std::cout << "Hello, this is NetLicensing demo client\n";
  std::cout << "Product endpoint " << endpoint<Product>() << std::endl;
  std::cout << "Product test number " << productNumber << std::endl;

  try {
    Context ctx;
    ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
    ctx.set_username("demo");
    ctx.set_password("demo");

    // product section
    Product p;
    p.setName("Test name");
    p.setNumber(productNumber);
    Product newp = ProductService::create(ctx, p);

    newp.setName("Updated name");
    Product newp2 = ProductService::update(ctx, newp.getNumber(), newp);

    std::list<Product> products = ProductService::list(ctx, "");
    std::cout << "before delete products count " << products.size() << std::endl;

    ProductService::del(ctx, newp2.getNumber(), false);

    products = ProductService::list(ctx, "");
    std::cout << "after delete products count " << products.size() << std::endl;
    
    if (!licensee_number.empty()) {
      std::cout << "start validation for " << licensee_number << std::endl;
      ValidationResult vres = LicenseeService::validate(ctx, licensee_number);
      std::cout << "got validation results:\n" << vres.toString() << std::endl;
    }
  }
  catch (const RestException& e) {
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
