#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include "netlicensing/constants.h"
#include "netlicensing/context.h"
#include "netlicensing/mapper.h"
#include "netlicensing/traversal.h"

namespace netlicensing {

template<class T> std::string endpoint();
template<> inline std::string endpoint<Product>() { return std::string(PRODUCT_ENDPOINT_PATH); }
template<> inline std::string endpoint<ProductModule>() { return std::string(PRODUCT_MODULE_ENDPOINT_PATH); }
template<> inline std::string endpoint<LicenseTemplate>() { return std::string(LICENSE_TEMPLATE_ENDPOINT_PATH); }
template<> inline std::string endpoint<Licensee>() { return std::string(LICENSEE_ENDPOINT_PATH); }
template<> inline std::string endpoint<License>() { return std::string(LICENSE_ENDPOINT_PATH); }
template<> inline std::string endpoint<PaymentMethod>() { return std::string(PAYMENT_METHOD_ENDPOINT_PATH); }
template<> inline std::string endpoint<Token>() { return std::string(TOKEN_ENDPOINT_PATH); }
template<> inline std::string endpoint<Transaction>() { return std::string(TRANSACTION_ENDPOINT_PATH); }
template<> inline std::string endpoint<Country>() { return std::string(UTILITY_ENDPOINT_PATH) + "/" +std::string(ENDPOINT_PATH_COUNTRIES); }
template<> inline std::string endpoint<LicensingModel>() { return UTILITY_ENDPOINT_PATH + "/" + std::string(ENDPOINT_PATH_LICENSING_MODELS); }
template<> inline std::string endpoint<LicenseType>() { return UTILITY_ENDPOINT_PATH + "/" + std::string(ENDPOINT_PATH_LICENSE_TYPES); }

template<typename M>
void getEntity(Context& ctx, M& mapper, const std::string& number) {
  long http_code;
  std::string res = ctx.get(endpoint<typename M::Item_t>() + "/" + escape_string(number), parameters_type(), http_code);
  traverse(mapper, res);
  if (http_code != 200) {
    throw RestException(mapper.getInfos(), http_code);
  }
}

template<typename T>
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
}

template<typename M, typename T>
void update_create(Context& ctx, M& mapper, const std::string& number, const T& value) {
  long http_code;
  std::string ep = endpoint<T>() + (number.empty()?"":("/" + escape_string(number)));
  std::string res = ctx.post(ep, toParametersList(value), http_code);
  traverse(mapper, res);
  if (http_code != 200) {
    throw RestException(mapper.getInfos(), http_code);
  }
}

template<typename M>
void get(Context& ctx, M& mapper, const std::string& number) {
  return getEntity(ctx, mapper, number);
}

template<typename M, typename T>
void update(Context& ctx, M& mapper, const std::string& number, const T& value) {
  return update_create(ctx, mapper, number, value);
}

template<typename M, typename T>
void create(Context& ctx, M& mapper, const T& value) {
  return update_create(ctx, mapper, std::string(), value);
}

template<typename M>
void list(Context& ctx, M& mapper, const std::string& filter) {
  parameters_type params;
  if (!filter.empty()) {
    params.push_back(std::make_pair(FILTER, filter));
  }

  long http_code;
  std::string res = ctx.get(endpoint<typename M::Item_t>(), params, http_code);
  traverse(mapper, res);
  
  // TODO(a-pavlov) fix code checking
  if (http_code != 200) {
    throw RestException(mapper.getInfos(), http_code);
  }
}

}

#endif //__SERVICE_HPP__
