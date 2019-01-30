#ifndef __PAYMENT_METHOD_H__
#define __PAYMENT_METHOD_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class PaymentMethod : public BaseEntity {
  private:

  public:

    std::string toString() const {
      std::string number(getNumber());
      Boolean_t active(getActive());

      std::stringstream ss;
      ss << "PaymentMethod [";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString();
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __PAYMENT_METHOD_H__
