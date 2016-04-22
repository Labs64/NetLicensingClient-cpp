#include "netlicensing/product.h"

namespace netlicensing {

void Discount::add_property(const std::string& name, const std::string& value) {
  if (FlatList<Discount>::add_property(name, value)) return;
  if (name == "totalPrice") total_price_ = value;
  else if (name == "currency") currency_ = value;
  else if (name == "amountPercent") amount_percent_ = value;
}

void Product::add_list(std::shared_ptr<PropertyType> ptr) {
  discounts_.push_back(ptr);
}
 
void Product::add_property(const std::string& name, const std::string& value) {
  if (name == "number") assign(number_, value);
  else if (name == "name") assign(name_, value);
  else if (name == "licenseeAutoCreate") assign(lic_auto_create_, value);
  else if (name == "inUse") assign(in_use_, value);
  else Entity::add_property(name, value);
}

}