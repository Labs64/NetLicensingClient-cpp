#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class Transaction : public BaseEntity {
  private:
    TransactionStatus status_i;
    TransactionSource source_i;
    FixedPoint grandTotal_i = FixedPoint(0);
    FixedPoint discount_i = FixedPoint(0);
    Currency currency_i;
    Date dateCreated_i;
    Date dateClosed_i;

  public:
    Transaction() : status_i(), source_i(), grandTotal_i(),
    discount_i(), currency_i(), dateCreated_i(), dateClosed_i() { }

    void setStatus(const TransactionStatus status) {
      status_i = status;
    }

    const TransactionStatus getStatus() const {
      return status_i;
    }

    void setSource(const TransactionSource source) {
      source_i = source;
    }

    const TransactionSource getSource() const {
      return source_i;
    }

    void setGrandTotal(const FixedPoint& grandTotal) {
      grandTotal_i = grandTotal;
    }

    const FixedPoint& getGrandTotal() const {
      return grandTotal_i;
    }

    void setDiscount(const FixedPoint& discount) {
      discount_i = discount;
    }

    const FixedPoint& getDiscount() const {
      return discount_i;
    }

    void setCurrency(const Currency currency) {
      currency_i = currency;
    }

    const Currency getCurrency() const {
      return currency_i;
    }

    void setDateCreated(const Date& dateCreated) {
      dateCreated_i = dateCreated;
    }

    const Date& getDateCreated() const {
      return dateCreated_i;
    }

    void setDateClosed(const Date& dateClosed) {
      dateClosed_i = dateClosed;
    }

    const Date& getDateClosed() const {
      return dateClosed_i;
    }

    std::string toString() const {
      std::string number(getNumber());
      Boolean_t active(getActive());
      std::string status(transactionStatusToString(getStatus()));
      std::string source(transactionSourceToString(getSource()));
      std::string grandTotal(getGrandTotal().toString());
      std::string discount(getDiscount().toString());
      std::string currency(currencyToString(getCurrency()));
      std::string dateCreated(getDateCreated().toString());
      std::string dateClosed(getDateClosed().toString());

      std::stringstream ss;
      ss << "Transaction [";
      ss << NUMBER << ": " << number << ", ";
      ss << ACTIVE << ": " << active.toString() << ", ";
      ss << STATUS << ": " << status << ", ";
      ss << SOURCE << ": " << source << ", ";
      ss << GRAND_TOTAL << ": " << grandTotal << ", ";
      ss << DISCOUNT << ": " << discount << ", ";
      ss << CURRENCY << ": " << currency << ", ";
      ss << DATE_CREATED << ": " << dateCreated << ", ";
      ss << DATE_CLOSED << ": " << dateClosed;

      for (const auto& pair : getProperties()) {
          ss << ", " << pair.first << ": " << pair.second.toString();
      }

      ss << "]";
      return ss.str();
    }
  };

}

#endif // __TRANSACTION_H__
