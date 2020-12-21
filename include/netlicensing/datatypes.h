#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <stdint.h>
#include <sstream>
#include <string>

#include "netlicensing/exception.h"

#ifdef __GNUC__
#define DEPRECATED(decl) decl __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(decl) __declspec(deprecated) decl
#else
#pragma message("WARNING: DEPRECATED declaration for this compiler is not defined")
#define DEPRECATED(decl) decl
#endif

namespace netlicensing {
  // This is a simplified version of std::optional (or boost::optional) to avoid dependency
  // on not yet widely supported C++17 or external library (boost).
  template <typename T>
  class Optional {
    bool available_i;
    T value_i;

  public:
    Optional() : available_i(false), value_i() {}
    Optional(T value) : available_i(true), value_i(value) {}
    Optional(const char* value);

    bool operator()() const { return available_i; }

    operator T() const { return value_i; }

    std::string toString() const;
  };

  //Date
  class Date {
    std::string value_i;//TODO(AY): change to real date

  public:
    Date(const std::string& value) {
        value_i = value;
    }
    Date() {
      value_i = "";
    }
    std::string toString() const {
      return value_i;
    }
  };

  // TODO(2K): Precision is currently fixed at 2 digits after decimal point, make variable
  class FixedPoint {
    int64_t value_i;

  public:
    FixedPoint(const std::string& value) {
      if (value == "0") {
        value_i = 0.00;
      } else if ((value.length() > 3) && (value[value.length() - 3] == '.')) {
        // TODO(2K): too primitive parsing - improve
        std::string rawValue = value;
        rawValue.erase(value.length() - 3, 1);
        std::istringstream is(rawValue);
        is >> value_i;
      } else {
        throw MalformedArgumentsException("Not supported formatting for fixed point value");
      }
    }
    FixedPoint() {
      value_i = 0.00;
    }

    std::string toString() const {
      std::ostringstream os;
      os << value_i;
      std::string sValue = os.str();
      if ((sValue != "0")) {
        sValue.insert(sValue.length() - 2, ".");
      }
      return sValue;
    }
  };


  typedef Optional<std::string> String_t;
  typedef Optional<FixedPoint> Decimal_t;
  typedef Optional<bool> Boolean_t;

  template<>
  inline Optional<std::string>::Optional(const char* value)
    : available_i(true), value_i(value) { }

  template<>
  inline std::string Optional<std::string>::toString() const {
    return value_i;
  }

  template<>
  inline std::string Optional<FixedPoint>::toString() const {
    return value_i.toString();
  }

  template<>
  inline Optional<bool>::Optional(const char* value)
    : available_i(true), value_i(std::string(value) == "true") { }

  template<>
  inline std::string Optional<bool>::toString() const {
    return value_i ? "true" : "false";
  }

  typedef std::list<std::pair<std::string, std::string> > parameters_type;

  enum class Currency {
    NONE,
    EUR,
    USD
  };
  inline const char* currencyToString(Currency v)
  {
    switch (v)
    {
      case Currency::NONE:  return "";
      case Currency::EUR:   return "EUR";
      case Currency::USD:   return "USD";
      default:    return "[Unknown Currency]";
    }
  }
  inline const Currency stringToCurrency(const String_t& v)
  {
    if (std::string(v) == "") return Currency::NONE;
    else if (std::string(v) == "EUR") return Currency::EUR;
    else if (std::string(v) == "USD") return Currency::USD;
    else return Currency::NONE;
  }

  enum class TokenType {
    DEFAULT,
    APIKEY,
    REGISTRATION,
    PASSWORDRESET,
    SHOP
  };
  inline const char* tokenTypeToString(TokenType v)
  {
    switch (v)
    {
      case TokenType::DEFAULT:  return "DEFAULT";
      case TokenType::APIKEY:   return "APIKEY";
      case TokenType::REGISTRATION:   return "REGISTRATION";
      case TokenType::PASSWORDRESET:   return "PASSWORDRESET";
      case TokenType::SHOP:   return "SHOP";
      default:    return "[Unknown TokenType]";
    }
  }
  inline const TokenType stringToTokenType(const String_t& v)
  {
    if (std::string(v) == "DEFAULT") return TokenType::DEFAULT;
    else if (std::string(v) == "APIKEY") return TokenType::APIKEY;
    else if (std::string(v) == "REGISTRATION") return TokenType::REGISTRATION;
    else if (std::string(v) == "PASSWORDRESET") return TokenType::PASSWORDRESET;
    else if (std::string(v) == "SHOP") return TokenType::SHOP;
    else return TokenType::DEFAULT;
  }
  enum class TransactionStatus {
    /**
     * Transaction still running.
     */
    PENDING,
    /**
     * Transaction is closed.
     */
    CLOSED,
    /**
     * Transaction is cancelled.
     */
    CANCELLED
  };
  inline const char* transactionStatusToString(TransactionStatus v)
  {
    switch (v)
    {
      case TransactionStatus::PENDING:     return "PENDING";
      case TransactionStatus::CLOSED:      return "CLOSED";
      case TransactionStatus::CANCELLED:   return "CANCELLED";
      default:          return "[Unknown TransactionStatus]";
    }
  }
  inline const TransactionStatus stringToTransactionStatus(const String_t& v)
  {
    if (std::string(v) == "PENDING") return TransactionStatus::PENDING;
    else if (std::string(v) == "CLOSED") return TransactionStatus::CLOSED;
    else if (std::string(v) == "CANCELLED") return TransactionStatus::CANCELLED;
    else return TransactionStatus::CLOSED;
  }

  enum class TransactionSource {
    /**
     * Shop transaction.
     */
    SHOP,

    /**
     * Auto transaction for license create.
     */
    AUTO_LICENSE_CREATE,

    /**
     * Auto transaction for license update.
     */
    AUTO_LICENSE_UPDATE,

    /**
     * Auto transaction for license delete.
     */
    AUTO_LICENSE_DELETE,

    /**
     * Auto transaction for licensee create (with automatic licenses).
     */
    AUTO_LICENSEE_CREATE,

    /**
     * Auto transaction for licensee delete with forceCascade.
     */
    AUTO_LICENSEE_DELETE,

    /**
     * Auto transaction for license template delete with forceCascade.
     */
    AUTO_LICENSETEMPLATE_DELETE,

    /**
     * Auto transaction for product module delete with forceCascade.
     */
    AUTO_PRODUCTMODULE_DELETE,

    /**
     * Auto transaction for product delete with forceCascade.
     */
    AUTO_PRODUCT_DELETE,

    /**
     * Auto transaction for transfer licenses between licensee.
     */
    AUTO_LICENSES_TRANSFER,

    /**
     * Transaction for update licenses (inactive with PT LM, Subscription).
     */
    SUBSCRIPTION_UPDATE,

    /**
     * Transaction for cancel recurring payment.
     */
    CANCEL_RECURRING_PAYMENT
  };
  inline const char* transactionSourceToString(TransactionSource v)
  {
    switch (v)
    {
      case TransactionSource::SHOP:                          return "SHOP";
      case TransactionSource::AUTO_LICENSE_CREATE:           return "AUTO_LICENSE_CREATE";
      case TransactionSource::AUTO_LICENSE_UPDATE:           return "AUTO_LICENSE_UPDATE";
      case TransactionSource::AUTO_LICENSE_DELETE:           return "AUTO_LICENSE_DELETE";
      case TransactionSource::AUTO_LICENSEE_CREATE:          return "AUTO_LICENSEE_CREATE";
      case TransactionSource::AUTO_LICENSEE_DELETE:          return "AUTO_LICENSEE_DELETE";
      case TransactionSource::AUTO_LICENSETEMPLATE_DELETE:   return "AUTO_LICENSETEMPLATE_DELETE";
      case TransactionSource::AUTO_PRODUCTMODULE_DELETE:     return "AUTO_PRODUCTMODULE_DELETE";
      case TransactionSource::AUTO_PRODUCT_DELETE:           return "AUTO_PRODUCT_DELETE";
      case TransactionSource::AUTO_LICENSES_TRANSFER:        return "AUTO_LICENSES_TRANSFER";
      case TransactionSource::SUBSCRIPTION_UPDATE:           return "SUBSCRIPTION_UPDATE";
      case TransactionSource::CANCEL_RECURRING_PAYMENT:      return "CANCEL_RECURRING_PAYMENT";
      default:                            return "[Unknown TransactionSource]";
    }
  }
  inline const TransactionSource stringToTransactionSource(const String_t& v)
  {
    if (std::string(v) == "SHOP")                     return TransactionSource::SHOP;
    else if (std::string(v) == "AUTO_LICENSE_CREATE") return TransactionSource::AUTO_LICENSE_CREATE;
    else if (std::string(v) == "AUTO_LICENSE_UPDATE") return TransactionSource::AUTO_LICENSE_UPDATE;
    else if (std::string(v) == "AUTO_LICENSE_DELETE") return TransactionSource::AUTO_LICENSE_DELETE;
    else if (std::string(v) == "AUTO_LICENSEE_CREATE") return TransactionSource::AUTO_LICENSEE_CREATE;
    else if (std::string(v) == "AUTO_LICENSEE_DELETE") return TransactionSource::AUTO_LICENSEE_DELETE;
    else if (std::string(v) == "AUTO_LICENSETEMPLATE_DELETE") return TransactionSource::AUTO_LICENSETEMPLATE_DELETE;
    else if (std::string(v) == "AUTO_PRODUCTMODULE_DELETE") return TransactionSource::AUTO_PRODUCTMODULE_DELETE;
    else if (std::string(v) == "AUTO_PRODUCT_DELETE") return TransactionSource::AUTO_PRODUCT_DELETE;
    else if (std::string(v) == "AUTO_LICENSES_TRANSFER") return TransactionSource::AUTO_LICENSES_TRANSFER;
    else if (std::string(v) == "SUBSCRIPTION_UPDATE") return TransactionSource::SUBSCRIPTION_UPDATE;
    else if (std::string(v) == "CANCEL_RECURRING_PAYMENT") return TransactionSource::CANCEL_RECURRING_PAYMENT;
    else return TransactionSource::SHOP;
  }
  enum class LicenseTypeEnum {
    /**
     * licenseType: Feature.
     */
    FEATURE,

    /**
     * licenseType: TimeVolume.
     */
    TIMEVOLUME,

    /**
     * licenseType: TimeVolume.
     */
    FLOATING,

    /**
     * licenseType: Quantity.
     */
    QUANTITY
  };
  inline const char* licenseTypeToString(LicenseTypeEnum v)
  {
    switch (v)
    {
      case LicenseTypeEnum::FEATURE:    return "FEATURE";
      case LicenseTypeEnum::TIMEVOLUME: return "TIMEVOLUME";
      case LicenseTypeEnum::FLOATING:   return "FLOATING";
      case LicenseTypeEnum::QUANTITY:   return "QUANTITY";
      default:                      return "[Unknown LicenseType]";
    }
  }
  inline const LicenseTypeEnum stringToLicenseType(const String_t& v)
  {
    if (std::string(v) == "FEATURE")          return LicenseTypeEnum::FEATURE;
    else if (std::string(v) == "TIMEVOLUME")  return LicenseTypeEnum::TIMEVOLUME;
    else if (std::string(v) == "FLOATING")    return LicenseTypeEnum::FLOATING;
    else if (std::string(v) == "QUANTITY")    return LicenseTypeEnum::QUANTITY;
    else return LicenseTypeEnum::FEATURE;
  }
}  // namespace netlicensing

#endif  // __DATATYPES_H__
