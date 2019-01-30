#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class Token : public BaseEntity {
  private:
    String_t vendorNumber_i;
    Date expirationTime_i;
    TokenType tokenType_i;

  public:
    Token() : vendorNumber_i(), expirationTime_i(), tokenType_i() { }

    void setVendorNumber(const String_t& vendorNumber) {
      vendorNumber_i = vendorNumber;
    }

    const String_t& getVendorNumber() const {
      return vendorNumber_i;
    }

    void setExpirationTime(const Date& expirationTime) {
      expirationTime_i = expirationTime;
    }

    const Date& getExpirationTime() const {
      return expirationTime_i;
    }

    void setTokenType(const TokenType tokenType) {
      tokenType_i = tokenType;
    }

    const TokenType getTokenType() const {
      return tokenType_i;
    }

    std::string toString() const {
      std::string number(getNumber());
      Boolean_t active(getActive());
      std::string vendorNumber(getVendorNumber());
      std::string expirationTime(getExpirationTime().toString());
      std::string tokenType(tokenTypeToString(getTokenType()));

      std::stringstream ss;
      ss << "Token [";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString() << ", ";
      ss << VENDOR_NUMBER << ": " << vendorNumber << ", ";
      ss << EXPIRATION_TIME << ": " << expirationTime << ", ";
      ss << TOKEN_TYPE << ": " << tokenType;
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __TOKEN_H__
