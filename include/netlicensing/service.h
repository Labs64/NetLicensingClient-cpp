#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include "netlicensing/context.h"

namespace netlicensing {

template<class T>
std::string endpoint();

template<class T>
T get(Context& ctx) {
  T res;
  std::string res = ctx.get();
};

template<class T>
T create(Context& ctx) {
  T item;
  //ctx.post(endpoint<T>(), );
};

};

#endif //__SERVICE_HPP__