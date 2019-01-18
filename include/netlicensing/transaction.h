#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include <list>

#include "netlicensing/entity.h"

namespace netlicensing {

  class Transaction : public BaseEntity {
  private:
    String_t status_i;//TODO(AY): change type to Status ?
    String_t source_i;//TODO(AY): change type to Source ?
    String_t grandTotal_i;//TODO(AY): change type to Num
    String_t discount_i;//TODO(AY): change type to Num
    String_t currency_i;//TODO(AY): change type to Currency
    String_t dateCreated_i;//TODO(AY): change type to Date
    String_t dateClosed_i;//TODO(AY): change type to Date

  public:
    Transaction() : status_i(), source_i(), grandTotal_i(),
    discount_i(), currency_i(), dateCreated_i(), dateClosed_i() { }

    void setStatus(const String_t& status) {
      status_i = status;
    }

    const String_t& getStatus() const {
      return status_i;
    }

    void setSource(const String_t& source) {
      source_i = source;
    }

    const String_t& getSource() const {
      return source_i;
    }

    void setGrandTotal(const String_t& grandTotal) {
      grandTotal_i = grandTotal;
    }

    const String_t& getGrandTotal() const {
      return grandTotal_i;
    }

    void setDiscount(const String_t& discount) {
      discount_i = discount;
    }

    const String_t& getDiscount() const {
      return discount_i;
    }

    void setCurrency(const String_t& currency) {
      currency_i = currency;
    }

    const String_t& getCurrency() const {
      return currency_i;
    }

    void setDateCreated(const String_t& dateCreated) {
      dateCreated_i = dateCreated;
    }

    const String_t& getDateCreated() const {
      return dateCreated_i;
    }

    void setDateClosed(const String_t& dateClosed) {
      dateClosed_i = dateClosed;
    }

    const String_t& getDateClosed() const {
      return dateClosed_i;
    }

    String_t toString() const {
      std::string number(this->getNumber());
      Boolean_t active(this->getActive());
      std::string status(this->getStatus());
      std::string source(this->getSource());
      std::string grandTotal(this->getGrandTotal());
      std::string discount(this->getDiscount());
      std::string currency(this->getCurrency());
      std::string dateCreated(this->getDateCreated());
      std::string dateClosed(this->getDateClosed());

      std::stringstream ss;
      ss << "Transaction [";
      ss << "number: ";
      ss << number;
      ss << ", ";
      ss << "active: ";
      ss << active.toString();
      ss << ", ";
      ss << "status: ";
      ss << status;
      ss << ", ";
      ss << "source: ";
      ss << source;
      ss << ", ";
      ss << "grandTotal: ";
      ss << grandTotal;
      ss << ", ";
      ss << "discount: ";
      ss << discount;
      ss << ", ";
      ss << "currency: ";
      ss << currency;
      ss << ", ";
      ss << "dateCreated: ";
      ss << dateCreated;
      ss << ", ";
      ss << "dateClosed: ";
      ss << dateClosed;
      ss << "]";
      return ss.str();
    }
  };

}

#endif // __TRANSACTION_H__
