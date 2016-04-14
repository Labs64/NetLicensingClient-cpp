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

    // check context direct call 
    std::list<std::pair<std::string, std::string> > params;
    params.push_back(std::make_pair("licenseeNumber", "1"));
    params.push_back(std::make_pair("licenseTemplateNumber", "1"));
    params.push_back(std::make_pair("active", "true"));
    params.push_back(std::make_pair("number", "1"));
    params.push_back(std::make_pair("name", "lic"));

    netlicensing::context ctx;
    ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
    ctx.set_username("demo");
    ctx.set_password("demo");
    std::string res = ctx.post("license", params);
    std::cout << "license check answer: " << res << std::endl;
	return 0;
}
