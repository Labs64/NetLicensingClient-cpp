#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <list>

#include "netlicensing/entity.h"

namespace netlicensing {

  class Token : public BaseEntity {
  private:
    String_t vendorNumber_i;
    String_t expirationTime_i;//TODO(AY):change to Date
    String_t tokenType_i;//TODO(AY):change to TokenType

  public:
    Token() : vendorNumber_i(), expirationTime_i(), tokenType_i() { }

    void setVendorNumber(const String_t& vendorNumber) {
      vendorNumber_i = vendorNumber;
    }

    const String_t& getVendorNumber() const {
      return vendorNumber_i;
    }

    void setExpirationTime(const String_t& expirationTime) {
      expirationTime_i = expirationTime;
    }

    const String_t& getExpirationTime() const {
      return expirationTime_i;
    }

    void setTokenType(const String_t& tokenType) {
      tokenType_i = tokenType;
    }

    const String_t& getTokenType() const {
      return tokenType_i;
    }

    String_t toString() const {
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());
      std::string vendorNumber(this->getVendorNumber());
      std::string expirationTime(this->getExpirationTime());
      std::string tokenType(this->getTokenType());

      std::stringstream ss;
      ss << "Token [";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << ", ";
      ss << "vendorNumber: ";
      ss << vendorNumber;
      ss << ", ";
      ss << "expirationTime: ";
      ss << expirationTime;
      ss << ", ";
      ss << "tokenType: ";
      ss << tokenType;
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __TOKEN_H__
