#include "netlicensing/service.h"
#include "netlicensing/product.h"

namespace netlicensing {

template<>
std::string endpoint<Product>() {
  return std::string("product");
};

};
