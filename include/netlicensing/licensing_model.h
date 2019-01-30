#ifndef __LICENSING_MODEL_H__
#define __LICENSING_MODEL_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class LicensingModel {
  private:
    String_t name_i;

  public:
    LicensingModel() : name_i() { }

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }

    std::string toString() const {
      std::string name(getName());

      std::stringstream ss;
      ss << "LicensingModel [";
      ss << NAME << ": " << name;
      ss << "]";
      return ss.str();
    }

  };

}

#endif // __LICENSING_MODEL_H__
