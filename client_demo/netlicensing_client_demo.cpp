#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>
#include <iterator>
#include "netlicensing/context.hpp"
#include "netlicensing/service.hpp"

struct pair2string {
    std::string operator()(const std::pair<std::string, std::string>& p) {
        return p.first + "=" + p.second;
    }
};

struct join_sep {
    std::string operator()(const std::string& s1, const std::string& s2) {
        if (s1.empty()) return s1 + s2;
        return s1 + "&" + s2;
    }
};

int main(int argc, char* argv[]) {
	std::cout << "Hello, this is NetLicensing demo client\n";
    netlicensing::string_context sc;
    sc.set_value("xx", "yy");
    std::cout << sc.get_value("xx") << std::endl;

    //const std::string res = netlicensing::service::get("http://netlicensing.io/");

    std::list<std::pair<std::string, std::string> > params;
    params.push_back(std::make_pair("licenseeNumber", "1"));
    params.push_back(std::make_pair("licenseTemplateNumber", "1"));
    params.push_back(std::make_pair("active", "true"));
    params.push_back(std::make_pair("number", "1"));
    params.push_back(std::make_pair("name", "lic"));

    //licenseeNumber = 1 & licenseTemplateNumber = 2 & active = true & number = 1 & name = xxx

    netlicensing::service::set_username("demo");
    netlicensing::service::set_password("demo");
    std::string res = netlicensing::service::send_post("https://go.netlicensing.io/core/v2/rest/license", params);
    std::cout << "res " << res << std::endl;

	return 0;
}
