#include <iostream>
#include <random>  
#include <ctime> 
#include <sstream>
#include <string>
#include "netlicensing/netlicensing.h"
#include "netlicensing/constants.h"

int main(int argc, char* argv[]) {
	using namespace netlicensing;

	std::string licensee_number;
	if (argc > 1) {
		licensee_number = argv[1];
	}

	std::mt19937 gen;
	gen.seed(time(0));
	std::stringstream ss;

	std::cout << "Hello, this is NetLicensing demo client\n";

	try {
		Context ctx;
		ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
		std::cout << "NetLicensing URL: https://go.netlicensing.io/core/v2/rest/" << std::endl;;
		ctx.set_username("demo");
		std::cout << "Account:demo" << std::endl;;
		ctx.set_password("demo");

		if (licensee_number.empty()) {
			do
			{
				std::cout << "Please enter a valid licensee number for validation (choose licensee in demo account): " << std::endl;
				std::getline(std::cin, licensee_number);

			} while (licensee_number.empty());

			std::cout << "start validation for " << licensee_number << std::endl;
			ValidationResult vres = LicenseeService::validate(ctx, licensee_number);
			std::cout << "got validation results:\n" << vres.toString() << std::endl;

			std::cout << "Please press enter key for exit"  << std::endl;
			std::cin.ignore();
		}
	}
	catch (const RestException& e) {
		std::cerr << e.what() << " code " << e.http_code() << std::endl;
		for (auto det : e.get_details()) {
			std::cerr << det.to_string() << std::endl;
		}
		std::cout << "Please press enter key for exit"  << std::endl;
		std::cin.ignore();
		return 2;
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cout << "Please press enter key for exit"  << std::endl;
		std::cin.ignore();
		return 1;
	}

	return 0;
}
