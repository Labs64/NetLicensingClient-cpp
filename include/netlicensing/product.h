#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include "netlicensing/entity.h"
#include "netlicensing/constants.h"

namespace netlicensing {

struct Discount : public FlatList<Discount> {
  std::string total_price_;
  std::string currency_;
  std::string amount_percent_;
  void add_property(const std::string& name, const std::string& value);
};

struct Product : public Entity {
 public:
  typedef Discount PropertyType;
 private:
  std::string number_;
  std::string name_;
  bool lic_auto_create_;
  bool in_use_;  

  std::list<std::shared_ptr<Discount> > discounts_;
 public:

  Product() : lic_auto_create_(false), in_use_(false) {}

  void add_list(std::shared_ptr<PropertyType> ptr);
  void add_property(const std::string& name, const std::string& value);
  parameters_type to_parameters_list() const;

  std::string getName() const { return name_; }
  std::string getNumber() const { return number_; }

  void setName(const std::string& name) { name_ = name; }
  void setNumber(const std::string& number) { number_ = number; }
  std::list<std::shared_ptr<PropertyType> > getDiscounts() const { return discounts_;  }
};

}

#endif //__PRODUCT_H__