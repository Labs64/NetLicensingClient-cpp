#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include "netlicensing/entity.h"

namespace netlicensing {

struct Discount : public FlatList<Discount> {
  std::string total_price_;
  std::string currency_;
  std::string amount_percent_;
  void add_property(const std::string& name, const std::string& value);
};

struct Product : public Entity {
  std::string number_;
  std::string name_;
  bool lic_auto_create_;
  bool in_use_;

  typedef Discount PropertyType;

  std::list<std::shared_ptr<Discount> > discounts_;

  Product() : lic_auto_create_(false), in_use_(false) {}

  void add_list(std::shared_ptr<PropertyType> ptr);
  void add_property(const std::string& name, const std::string& value);
};

}

#endif //__PRODUCT_H__