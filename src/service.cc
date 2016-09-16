#include "netlicensing/service.h"
#include "netlicensing/product.h"
#include "netlicensing/licensee.h"

namespace netlicensing {

template<>
std::string endpoint<Product>() {
  return std::string("product");
};

template<>
std::string endpoint<Licensee>() {
	return std::string("licensee");
};

};
