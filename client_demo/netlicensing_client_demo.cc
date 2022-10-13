#include <iostream>
#include <random>  
#include <ctime> 
#include <sstream>
#include "netlicensing/netlicensing.h"
#include "netlicensing/constants.h"
#include "netlicensing/validation_parameters.h"
#include "netlicensing/context.h"
#include "netlicensing/constants.h"
#include "netlicensing/datatypes.h"
#include "netlicensing/entity.h"

void cleanUp (netlicensing::Context& ctx, const std::string& productNumber, bool forceCascade) {
  //clean up
  try {
    netlicensing::ProductService::del(ctx, productNumber, forceCascade);
  } catch (const netlicensing::RestException& e) {
    std::cout << "Got NetLicensing exception during cleanup:" << std::endl;
    std::cerr << e.what() << std::endl;
    for (auto det : e.get_details()) {
      std::cerr << det.to_string() << std::endl;
    }
  } catch (const std::runtime_error& err) {
    std::cout << "Got exception during cleanup:" << std::endl;
    std::cerr << err.what() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  using namespace netlicensing;

  //generate random number
  std::mt19937 gen;
  gen.seed((unsigned int) time(0));
  std::stringstream ss;
  ss << gen();
  std::string randomNumber = ss.str();

  std::string productNumber = "P"+randomNumber;
  std::string productModuleNumber = "PM"+randomNumber;
  std::string licenseTemplateNumber = "LT"+randomNumber;
  std::string licenseeNumber = "L"+randomNumber;
  std::string licenseNumber = "LC"+randomNumber;
  std::string licenseeName = "Licensee "+randomNumber;

  std::cout << "Hello, this is NetLicensing demo client\n";
  std::cout << "Product endpoint " << endpoint<Product>() << std::endl;
  std::cout << "Product test number " << productNumber << std::endl;

  Context ctx;
  ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
  ctx.set_username("demo");
  ctx.set_password("demo");

  try {

    // region ********* Lists

    std::list<LicenseType> licenseTypes = UtilityService::listLicenseTypes(ctx);
    if (licenseTypes.size()) {
      std::cout << "License Types:" << std::endl;
      for (auto const& i : licenseTypes) {
        std::cout << i.toString() << std::endl;
      }
    }

    std::list<LicensingModel> licensingModels = UtilityService::listLicensingModels(ctx);
    if (licensingModels.size()) {
      std::cout << "LicensingModel:" << std::endl;
      for (auto const& i : licensingModels) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* Product

    Product newProduct;
    newProduct.setName("Demo product");
    newProduct.setNumber(productNumber);
    Product product = ProductService::create(ctx, newProduct);
    std::cout << "Added product: " << product.getName().toString() << std::endl;

    std::string productString(product.toString());

    product = ProductService::get(ctx, productNumber);
    std::cout << "Got product: " << productString << std::endl;

    std::list<Product> products = ProductService::list(ctx, "");
    if (products.size()) {
      std::cout << "Got the following products:" << std::endl;
      for (auto const& i : products) {
        std::cout << i.toString() << std::endl;
      }
    }

    newProduct.setName("Updated name");
    newProduct = ProductService::update(ctx, newProduct.getNumber(), newProduct);
    productString = newProduct.toString();
    std::cout << "Updated product: " << productString << std::endl;

    product = ProductService::get(ctx, productNumber);

    ProductService::del(ctx, product.getNumber(), false);
    std::cout << "Deleted Product!" << std::endl;

    products = ProductService::list(ctx, "");
    if (products.size()) {
      std::cout << "Got the following products:" << std::endl;
      for (auto const& i : products) {
        std::cout << i.toString() << std::endl;
      }
    }

    newProduct.setName("New Product");
    product = ProductService::create(ctx, newProduct);
    productString = product.toString();
    std::cout << "Added product again: " << productString << std::endl;

    products = ProductService::list(ctx, "");
    if (products.size()) {
      std::cout << "Got the following products:" << std::endl;
      for (auto const& i : products) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* Product Module

    ProductModule newProductModule;
    newProductModule.setNumber(productModuleNumber);
    newProductModule.setName("Demo product module");
    newProductModule.setLicensingModel(LICENSING_MODEL_TRY_AND_BUY_NAME);
    newProductModule.setProductNumber(productNumber);

    ProductModule productModule = ProductModuleService::create(ctx, newProductModule);
    std::cout << "Added product module: " << productModule.getName().toString() << std::endl;

    productModule = ProductModuleService::get(ctx, productModuleNumber);
    std::string productModuleString(productModule.toString());
    std::cout << "Got product module: " << productModuleString << std::endl;

    std::list<ProductModule> productModules = ProductModuleService::list(ctx, "");
    if (productModules.size()) {
      std::cout << "Got the following product modules: " << std::endl;
      for (auto const& i : productModules) {
        std::cout << i.toString() << std::endl;
      }
    }

    newProductModule.setName("Updated name");
    newProductModule = ProductModuleService::update(ctx, newProductModule.getNumber(), newProductModule);
    productModuleString = newProductModule.toString();
    std::cout << "Updated product module: " << productModuleString << std::endl;

    ProductModuleService::del(ctx, newProductModule.getNumber(), false);
    std::cout << "Deleted Product Module!" << std::endl;

    productModules = ProductModuleService::list(ctx, "");
    if (productModules.size()) {
      std::cout << "Got the following product modules: " << std::endl;
      for (auto const& i : productModules) {
        std::cout << i.toString() << std::endl;
      }
    }

    newProductModule.setName("Demo product module");
    productModule = ProductModuleService::create(ctx, newProductModule);
    std::cout << "Added product module again: " << productModule.getName().toString() << std::endl;

    productModules = ProductModuleService::list(ctx, "");
    if (productModules.size()) {
      std::cout << "Got the following product modules: " << std::endl;
      for (auto const& i : productModules) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* LicenseTemplate

    LicenseTemplate newLicenseTemplate;
    newLicenseTemplate.setNumber(licenseTemplateNumber);
    newLicenseTemplate.setName("Demo Evaluation Period");
    newLicenseTemplate.setLicenseType(LicenseTypeEnum::FEATURE);
    newLicenseTemplate.setPrice(FixedPoint("12.50"));
    newLicenseTemplate.setCurrency(Currency::EUR);
    newLicenseTemplate.setAutomatic(false);
    newLicenseTemplate.setHidden(false);
    newLicenseTemplate.setProductModuleNumber(productModuleNumber);
    LicenseTemplate licenseTemplate = LicenseTemplateService::create(ctx, newLicenseTemplate);
    std::cout << "Added license template: " << licenseTemplate.getName().toString() << std::endl;

    licenseTemplate = LicenseTemplateService::get(ctx, licenseTemplateNumber);
    std::string licenseTemplateString(licenseTemplate.toString());
    std::cout << "Got license template: " << licenseTemplateString << std::endl;

    std::list<LicenseTemplate> licenseTemplates = LicenseTemplateService::list(ctx, "");
    if (licenseTemplates.size()) {
      std::cout << "Got the following license templates: " << std::endl;
      for (auto const& i : licenseTemplates) {
        std::cout << i.toString() << std::endl;
      }
    }

    newLicenseTemplate.setName("Updated name");
    newLicenseTemplate = LicenseTemplateService::update(ctx, newLicenseTemplate.getNumber(), newLicenseTemplate);
    licenseTemplateString = newLicenseTemplate.toString();
    std::cout << "Updated license template: " << licenseTemplateString << std::endl;

    LicenseTemplateService::del(ctx, newLicenseTemplate.getNumber(), true);
    std::cout << "Deleted license template!" << std::endl;

    licenseTemplates = LicenseTemplateService::list(ctx, "");
    if (licenseTemplates.size()) {
      std::cout << "Got the following license templates: " << std::endl;
      for (auto const& i : licenseTemplates) {
        std::cout << i.toString() << std::endl;
      }
    }

    newLicenseTemplate.setName("Demo Evaluation Period");
    licenseTemplate = LicenseTemplateService::create(ctx, newLicenseTemplate);
    std::cout << "Added license template again: " << licenseTemplate.getName().toString() << std::endl;

    licenseTemplates = LicenseTemplateService::list(ctx, "");
    if (licenseTemplates.size()) {
      std::cout << "Got the following license templates: " << std::endl;
      for (auto const& i : licenseTemplates) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* Licensee

    Licensee newLicensee;
    newLicensee.setName("Demo licensee");
    newLicensee.setNumber(licenseeNumber);
    newLicensee.setProductNumber(productNumber);
    Licensee licensee = LicenseeService::create(ctx, newLicensee);
    std::cout << "Added licensee: " << licensee.getName().toString() << std::endl;

    std::string licenseeString(licensee.toString());

    std::list<Licensee> licensees = LicenseeService::list(ctx, "");
    if (licensees.size()) {
      std::cout << "Got the following licensees:" << std::endl;
      for (auto const& i : licensees) {
        std::cout << i.toString() << std::endl;
      }
    }

    LicenseeService::del(ctx, licenseeNumber, true);
    std::cout << "Deleted licensee!" << std::endl;

    licensees = LicenseeService::list(ctx, "");
    if (licensees.size()) {
      std::cout << "Got the following licensees after delete: " << std::endl;
      for (auto const& i : licensees) {
        std::cout << i.toString() << std::endl;
      }
    }

    licensee = LicenseeService::create(ctx, newLicensee);
    std::cout << "Added licensee again: " << licensee.getName().toString() << std::endl;

    licensee = LicenseeService::get(ctx, licenseeNumber);
    licenseeString = licensee.toString();
    std::cout << "Got licensee: " << licenseeString << std::endl;

    // endregion

    // region ********* License

    License newLicense;
    newLicense.setName("Demo license");
    newLicense.setNumber(licenseNumber);
    newLicense.setLicenseTemplateNumber(licenseTemplateNumber);
    newLicense.setLicenseeNumber(licenseeNumber);
    newLicense.setPrice(FixedPoint("1.00"));
    License license = LicenseService::create(ctx, newLicense);
    std::cout << "Added license: " << license.getName().toString() << std::endl;

    std::string licenseString(license.toString());

    std::list<License> licenses = LicenseService::list(ctx, "");
    if (licenses.size()) {
      std::cout << "Got the following licenses:" << std::endl;
      for (auto const& i : licenses) {
        std::cout << i.toString() << std::endl;
      }
    }

    LicenseService::del(ctx, licenseNumber, true);
    std::cout << "Deleted license!" << std::endl;

    licenses = LicenseService::list(ctx, "");
    if (licenses.size()) {
      std::cout << "Got the following licenses: " << std::endl;
      for (auto const& i : licenses) {
        std::cout << i.toString() << std::endl;
      }
    }

    license = LicenseService::create(ctx, newLicense);
    std::cout << "Added license again: " << license.getName().toString() << std::endl;

    license = LicenseService::get(ctx, licenseNumber);
    licenseString = license.toString();
    std::cout << "Got license: " << licenseString << std::endl;

    // endregion

    // region ********* PaymentMethod

    std::list<PaymentMethod> paymentMethods = PaymentMethodService::list(ctx, "");
    if (paymentMethods.size()) {
      std::cout << "Got the payment methods:" << std::endl;
      for (auto const& i : paymentMethods) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* Token

    Token newToken;
    newToken.setTokenType(TokenType::APIKEY);
    Token apiKey = TokenService::create(ctx, newToken);
    std::cout << "Created APIKey: " << apiKey.getNumber().toString() << std::endl;

    newToken.setTokenType(TokenType::SHOP);
    newToken.addProperty(LICENSEE_NUMBER, licenseeNumber);
    ctx.set_security_mode(netlicensing::Context::APIKEY_IDENTIFICATION);
    ctx.set_api_key(apiKey.getNumber().toString());
    Token shopToken = TokenService::create(ctx, newToken);
    ctx.set_security_mode(netlicensing::Context::BASIC_AUTHENTICATION);
    std::string tokenString(shopToken.toString());
    std::cout << "Got the following shop token: " << tokenString << std::endl;

    std::list<Token> tokens = TokenService::list(ctx, std::string(TOKEN_TYPE)+"="+tokenTypeToString(TokenType::SHOP));
    if (tokens.size()) {
      std::cout << "Got the following shop tokens: " << std::endl;
      for (auto const& i : tokens) {
        std::cout << i.toString() << std::endl;
      }
    }

    TokenService::del(ctx, shopToken.getNumber(), true);
    std::cout << "Deleted shop token!" << std::endl;

    tokens = TokenService::list(ctx, std::string(TOKEN_TYPE)+"="+tokenTypeToString(TokenType::SHOP));
    if (tokens.size()) {
      std::cout << "Got the following shop tokens after delete: " << std::endl;
      for (auto const& i : tokens) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* Validate

    ValidationParameters vParams = ValidationParameters();
    vParams.setProductModuleValidationParameters(productModuleNumber, "paramKey", "paramValue");
    vParams.setLicenseeName(licenseeName);
    vParams.setProductNumber(productNumber);
    vParams.setLicenseeProperty("some-licensee-property-key","some-licensee-property-value");
    ValidationResult vres = LicenseeService::validate(ctx, licenseeNumber, vParams);
    std::cout << "Validation result for created licensee:\n" << vres.toString() << std::endl;

    parameters_type params;
    params.push_back(std::make_pair("some-licensee-property-key", escape_string("some-licensee-property-value")));
    ValidationResult vres2 = LicenseeService::validate(ctx, licenseeNumber, productNumber, licenseeName, params);
    std::cout << "Validation result for created licensee:\n" << vres2.toString() << std::endl;

    // endregion

    // region ********* Transfer
    Licensee transferLicensee;
    transferLicensee.setNumber("TR" + licenseeNumber);
    transferLicensee.setProductNumber(productNumber);
    transferLicensee.addProperty(PROP_MARKED_FOR_TRANSFER, "true");
    transferLicensee = LicenseeService::create(ctx, transferLicensee);
    std::cout << "Added transfer licensee: " << transferLicensee.getNumber().toString() << std::endl;

    License transferLicense;
    transferLicense.setNumber("LTR" + licenseNumber);
    transferLicense.setLicenseTemplateNumber(licenseTemplateNumber);
    transferLicense.setLicenseeNumber(transferLicensee.getNumber());
    License newTransferLicense = LicenseService::create(ctx, transferLicense);
    std::cout << "Added license for transfer: " << transferLicense.getNumber().toString() << std::endl;

    LicenseeService::transfer(ctx, licensee.getNumber(), transferLicensee.getNumber());

    licenses = LicenseService::list(ctx, std::string(LICENSEE_NUMBER)+"="+licensee.getNumber().toString());
    if (licenses.size()) {
      std::cout << "Got the following licenses after transfer:" << std::endl;
      for (auto const& i : licenses) {
        std::cout << i.toString() << std::endl;
      }
    }

    Licensee transferLicenseeWithApiKey;
    transferLicenseeWithApiKey.setNumber("Key" + licenseeNumber);
    transferLicenseeWithApiKey.setProductNumber(productNumber);
    transferLicenseeWithApiKey.addProperty(PROP_MARKED_FOR_TRANSFER, "true");
    transferLicenseeWithApiKey = LicenseeService::create(ctx, transferLicenseeWithApiKey);
    std::cout << "Added licensee for transfer: " << transferLicenseeWithApiKey.getNumber().toString() << std::endl;

    License transferLicenseWithApiKey;
    transferLicenseWithApiKey.setNumber("Key" + licenseNumber);
    transferLicenseWithApiKey.setLicenseTemplateNumber(licenseTemplateNumber);
    transferLicenseWithApiKey.setLicenseeNumber(transferLicenseeWithApiKey.getNumber());
    LicenseService::create(ctx, transferLicenseWithApiKey);

    ctx.set_security_mode(netlicensing::Context::APIKEY_IDENTIFICATION);
    LicenseeService::transfer(ctx, licensee.getNumber(), transferLicenseeWithApiKey.getNumber());
    ctx.set_security_mode(netlicensing::Context::BASIC_AUTHENTICATION);

    licenses = LicenseService::list(ctx, std::string(LICENSEE_NUMBER)+"="+licensee.getNumber().toString());
    if (licenses.size()) {
      std::cout << "Got the following licenses after transfer: " << std::endl;
      for (auto const& i : licenses) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    // region ********* Transactions
    std::list<Transaction> transactions = TransactionService::list(ctx, std::string(SOURCE_SHOP_ONLY)+"=true");
    if (transactions.size()) {
      std::cout << "Got the following transactions shop only: " << std::endl;
      for (auto const& i : transactions) {
        std::cout << i.toString() << std::endl;
      }
    }

    transactions = TransactionService::list(ctx, "");
    if (transactions.size()) {
      std::cout << "Got the following transactions after transfer: " << std::endl;
      for (auto const& i : transactions) {
        std::cout << i.toString() << std::endl;
      }
    }

    // endregion

    std::cout << "All done." << std::endl;

    cleanUp(ctx, productNumber, true);

    std::cout << "Clean up!" << std::endl;
  }
  catch (const RestException& e) {
    std::cerr << e.what() << " code " << e.http_code() << std::endl;
    for (auto det : e.get_details()) {
      std::cerr << det.to_string() << std::endl;
    }

    cleanUp(ctx, productNumber, true);

    return 2;
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;

    cleanUp(ctx, productNumber, true);
    return 1;
  }

  return 0;
}
