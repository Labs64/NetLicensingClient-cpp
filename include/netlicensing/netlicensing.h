#ifndef __NETLICENSING_H__
#define __NETLICENSING_H__

#include "netlicensing/context.h"
#include "netlicensing/service.h"
#include "netlicensing/product.h"
#include "netlicensing/exception.h"

namespace netlicensing {

class ValidationService {
 public:
  static std::list<ValidationResult> validate(Context& ctx, const std::string& licenseNumber, 
    const std::string& productNumber = std::string(),
    const std::string& licenseeName = std::string());
};

class ProductService {
public:
  static Product create(Context& ctx, const Product&);
  static Product update(Context& ctx, const std::string& productNumber, const Product&);
  static void del(Context& ctx, const std::string& productNumber, bool forceCascade);
  static std::list<Product> list(Context& ctx, const std::string& filter);
};


}

#endif //__NETLICENSING_H__