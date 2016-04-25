#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include "netlicensing/context.h"
#include "netlicensing/validation_result.h"
#include "netlicensing/mapper.h"
#include "netlicensing/traversal.h"
#include "netlicensing/exception.h"

namespace netlicensing {

template<class T>
std::string endpoint();

template<class T>
T get(Context& ctx, const std::string& number) {
  long http_code;
  std::string res = ctx.get(endpoint<T>() + "/" + escape_string(number), parameters_type(), http_code);
  Mapper<T> mp;
  traverse(mp, res);
  if (http_code != 200) {
    throw RestException(mp.info_, http_code);
  }

  return mp.info_.front();
};

template<class T>
void del(Context& ctx, const std::string& number, bool force_cascade) {
  parameters_type params;
  if (force_cascade) {
    params.push_back(std::make_pair(CASCADE, "true"));
  }

  long http_code;
  ctx.del(endpoint<T>() + "/" + escape_string(number), params, http_code);
  if (http_code != 200 && http_code != 204) {
    throw RestException(std::list<Info>(), http_code);
  }
};

template<class T>
T update_create(Context& ctx, const std::string& number, const T& value) {
  long http_code;
  std::string ep = endpoint<T>() + (number.empty()?"":("/" + escape_string(number)));
  std::string res = ctx.post(ep, value.to_parameters_list(), http_code);
  Mapper<T> mp;
  traverse(mp, res);
  
  if (http_code != 200) {
    throw RestException(mp.info_, http_code);
  }

  return mp.items.front();
};

template<class T>
T update(Context& ctx, const std::string& number, const T& value) {
  return update_create(ctx, number, value);
}

template<class T>
T create(Context& ctx, const T& value) {
  return update_create(ctx, std::string(), value);
}

template<class T>
std::list<T> list(Context& ctx, const std::string& filter) {
  parameters_type params;
  if (!filter.empty()) {
    params.push_back(std::make_pair(FILTER, escape_string(filter)));
  }

  long http_code;
  std::string res = ctx.get(endpoint<T>(), params, http_code);
  Mapper<T> mp;
  traverse(mp, res);
  
  // TODO(a-pavlov) fix code checking
  if (http_code != 200) {
    throw RestException(mp.info_, http_code);
  }

  return mp.items;
}

inline std::list<ValidationResult> validate(Context& ctx, 
  const std::string& licensee_number,
  const std::string& product_number = std::string(),
  const std::string& licensee_name = std::string()) {
  std::string endpoint = "licensee/" + escape_string(licensee_number) + "/validate";
  parameters_type params;
  if (!product_number.empty()) params.push_back(std::make_pair("productNumber", escape_string(product_number)));
  if (!licensee_name.empty()) params.push_back(std::make_pair("licenseeName", escape_string(licensee_name)));

  long http_code;
  std::string res = ctx.get(endpoint, params, http_code);
  Mapper<ValidationResult> mp;
  traverse(mp, res);

  if (http_code != 200) {
    throw RestException(mp.info_, http_code);
  }
  
  return mp.items;
}

};

#endif //__SERVICE_HPP__
