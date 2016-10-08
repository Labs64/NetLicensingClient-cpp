#ifndef __LICENSEE_H__
#define __LICENSEE_H__

#include "netlicensing/entity.h"

namespace netlicensing {

  class Licensee : public BaseEntity {
    String_t name_i;

  public:
    Licensee() : name_i() {}

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }
  };

}  // namespace netlicensing

#endif  // __LICENSEE_H__