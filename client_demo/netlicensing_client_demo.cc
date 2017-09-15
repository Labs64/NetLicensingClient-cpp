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

		std::list<ProductDiscount> discounts;
		ProductDiscount discount;
		ProductDiscount discount2;

		discount.setTotalPrice("20");
		discount.setCurrency("EUR");
		discount.setAmountFix("10");

		discount2.setTotalPrice("25");
		discount2.setCurrency("EUR");
		discount2.setAmountPercent("10");

		discounts.push_back(discount);
		discounts.push_back(discount2);

		p.setProductsDiscounts(discounts);

		Product newp = ProductService::create(ctx, p);

		std::list<ProductDiscount> newpDiscounts = newp.getDiscounts();

		std::cout << "product disounts size: " << newpDiscounts.size() << std::endl;

		int i = 0;
		for (ProductDiscount newpDiscount : newpDiscounts) {
			std::string newpDiscountStr = newpDiscount.toString();
			std::cout << "product disount #" << i << ":" << newpDiscountStr << std::endl;
			i++;
		}

		newp.setName("Updated name");

		std::list<ProductDiscount> discountsEmpty;
		newp.setProductsDiscounts(discountsEmpty);
		std::cin.ignore();
		Product newp2 = ProductService::update(ctx, newp.getNumber(), newp);

		std::list<ProductDiscount> newp2Discounts = newp2.getDiscounts();

		std::cout << "product disounts size " << newp2Discounts.size() << std::endl;
		std::cin.ignore();
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
		std::cin.ignore();
		return 1;
	}

	return 0;
}
