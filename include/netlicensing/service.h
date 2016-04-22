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

inline std::list<ValidationResult> validate(Context& ctx, const std::string& licensee_number) {
  std::string endpoint = "licensee/" + licensee_number + "/validate";
  std::string res = ctx.get(endpoint, Context::parameters_type());
  Mapper<ValidationResult> mp;
  traverse(mp, res);
  return mp.items;
}

};

#endif //__SERVICE_HPP__
