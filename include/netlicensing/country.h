#ifndef __COUNTRY_H__
#define __COUNTRY_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class Country : public BaseEntity {
  private:
    String_t code_i;
    String_t name_i;
    Boolean_t isEu_i;
    String_t vatPercent_i;


  public:
    Country() : code_i(), name_i(), isEu_i(false) { }

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }

    void setIsEu(const Boolean_t& isEu) {
      isEu_i = isEu;
    }

    const Boolean_t& getIsEu() const {
      return isEu_i;
    }

    void setCode(const String_t& code) {
      code_i = code;
    }

    const String_t& getCode() const {
      return code_i;
    }

    void setVatPercent(const String_t& vatPercent) {
      vatPercent_i = vatPercent;
    }

    const String_t& getVatPercent() const {
      return vatPercent_i;
    }

    String_t toString() const {
      std::string name(this->getName());
      std::string isEu(this->getIsEu() == true?"true":"false");
      std::string code(this->getCode());
      std::string vatPercent(this->getVatPercent());

      std::stringstream ss;
      ss << "Country [";
      ss << NAME;
      ss << ": ";
      ss << name;
      ss << ", ";
      ss << "isEu: ";
      ss << isEu;
      ss << ", ";
      ss << "code: ";
      ss << code;
      ss << ", ";
      ss << "vatPercent: ";
      ss << vatPercent;
      ss << "]";
      return ss.str();
    }
    
  };

}

#endif // __COUNTRY_H__
