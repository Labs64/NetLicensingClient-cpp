#ifndef __PAYMENT_METHOD_H__
#define __PAYMENT_METHOD_H__

#include <list>

#include "netlicensing/entity.h"

namespace netlicensing {

  class PaymentMethod : public BaseEntity {
  private:

  public:

    String_t toString() const {
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());

      std::stringstream ss;
      ss << "PaymentMethod [";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __PAYMENT_METHOD_H__
