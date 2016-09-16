#include "netlicensing/licensee.h"

namespace netlicensing 
{
	void Licensee::add_property(const std::string& name, const std::string& value) 
	{
		if (name == "number")				assign(number_, value);
		else if (name == "name")			assign(name_, value);
		else if (name == "productNumber")	assign(product_, value);
		else if (name == "active")			assign(active_, value);
		else Entity::add_property(name, value);
	}

	parameters_type Licensee::to_parameters_list() const 
	{
		parameters_type params;
		params.push_back(std::make_pair("number", number_));
		params.push_back(std::make_pair("name", name_));
		params.push_back(std::make_pair("productNumber", product_));
		params.push_back(std::make_pair("active", active_ ? "true" : "false"));
		params.splice(params.end(), Entity::to_parameters_list());
		return params;
	}

}