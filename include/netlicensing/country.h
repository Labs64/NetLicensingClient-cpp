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

    std::string toString() const {
      std::string name(getName());
      std::string isEu(getIsEu() == true?"true":"false");
      std::string code(getCode());
      std::string vatPercent(getVatPercent());

      std::stringstream ss;
      ss << "Country [";
      ss << NAME << ": " << name << ", ";
      ss << "isEu: " << isEu << ", ";
      ss << "code: " << code << ", ";
      ss << "vatPercent: " << vatPercent;

      for (const auto& pair : getProperties()) {
          ss << ", " << pair.first << ": " << pair.second.toString();
      }

      ss << "]";
      return ss.str();
    }
    
  };

}

#endif // __COUNTRY_H__
