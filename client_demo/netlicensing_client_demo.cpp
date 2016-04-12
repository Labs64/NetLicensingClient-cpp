#include <iostream>
#include "netlicensing/context.hpp"
#include "netlicensing/service.hpp"

int main(int argc, char* argv[]) {
	std::cout << "Hello, this is NetLicensing demo client\n";
    netlicensing::string_context sc;
    sc.set_value("xx", "yy");
    std::cout << sc.get_value("xx") << std::endl;

    const std::string res = netlicensing::service::get("http:://ya.ru");
    std::cout << "res " << res << std::endl;
	return 0;
}
