#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include "netlicensing/context.h"
#include "netlicensing/validation_result.h"
#include "netlicensing/mapper.h"
#include "netlicensing/traversal.h"

namespace netlicensing {

template<class T>
std::string endpoint();

template<class T>
T get(Context& ctx) {
  T res;
  //std::string res = ctx.get();
  return res;
};

template<class T>
T create(Context& ctx) {
  T item;
  //ctx.post(endpoint<T>(), );
};

inline std::list<ValidationResult> validate(Context& ctx, 
  const std::string& licensee_number,
  const std::string& product_number = std::string(),
  const std::string& licensee_name = std::string()) {
  std::string endpoint = "licensee/" + licensee_number + "/validate";
  Context::parameters_type params;
  if (!product_number.empty()) params.push_back(std::make_pair("productNumber", product_number));
  if (!licensee_name.empty()) params.push_back(std::make_pair("licenseeName", licensee_name));
  long http_code;
  std::string res = ctx.get(endpoint, params, http_code);
  Mapper<ValidationResult> mp;
  traverse(mp, res);
  return mp.items;
}

};

#endif //__SERVICE_HPP__
