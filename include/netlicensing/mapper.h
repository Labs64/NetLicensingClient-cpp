#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <string>
#include <list>
#include <json/json.h>
#include <sstream>
#include <cassert>

#include "netlicensing/product.h"
#include "netlicensing/validation_result.h"

namespace netlicensing {

template<typename S, typename T>
void lexical_cast(T& t, const S& s) {
  std::stringstream stream;
  if (!(stream << s) || !(stream >> t) || !(stream >> std::ws).eof()) {
    throw std::bad_cast();
  }
}

inline void assign(std::string& target, const std::string& source) {
  target = source;
}

inline void assign(bool& target, const std::string& source) {
  if (source == "true") target = true;
  else if (source == "false") target = false;
  else throw std::logic_error("Value can not be interpret as logic");
}

inline void assign(int& target, const std::string& source) {
  lexical_cast(target, source);
}

template<class T>
class Mapper {
 public:

  std::list<T> items;
  inline void start_item() {
    items.push_back(T());
  }

  inline void set_property(const Json::Value& elem);
};

template<>
void Mapper<Product>::set_property(const Json::Value& elem) {
  if (elem["name"] == "number") assign(items.back().number_, elem["value"].asString());
  if (elem["name"] == "name") assign(items.back().name_, elem["value"].asString());
  if (elem["name"] == "licenseeAutoCreate") assign(items.back().lic_auto_create_, elem["value"].asString());
  if (elem["name"] == "inUse") assign(items.back().in_use_, elem["value"].asString());
}


template<>
class Mapper<ValidationResult> {
 public:
  std::list<ValidationResult> validations;
  std::shared_ptr<ValidationProperty> sentinel_;
  std::deque<std::shared_ptr<ValidationProperty> >  properties_stack_;
  int level_;

  Mapper() : level_(0) {}

  std::string root_name() const { return "items";  }

  void start_item(const std::string& name) {
    if (properties_stack_.empty() && name == "item") {
      assert(level_ == 0);
      validations.push_back(ValidationResult());
    }
    else {
      std::shared_ptr<ValidationProperty> prop(new ValidationProperty());
      if (properties_stack_.empty()) {
        validations.back().properties_.push_back(prop);
      } 
      else {
        properties_stack_.front()->next_properties_.push_back(prop);
      }

      properties_stack_.push_front(prop);
    }

    ++level_;
  }

  void end_item() {
    if (!properties_stack_.empty()) properties_stack_.pop_front();
    --level_;
  }

  void add_property(const std::string& name, const std::string& value) {
    if (properties_stack_.empty()) {
      // fill direct validation data
      if (name == "productModuleNumber") validations.back().product_module_number_ = value;
      else if (name == "productModuleName") validations.back().product_module_name_ = value;
      else if (name == "licensingModel") validations.back().licensing_model_ = value;
    }
    else {
      properties_stack_.front()->values.add_property(name, value);
    }
  }
};

template<typename T>
void fromJson(T& t, const std::string&);

template<class T>
void json_enumerator(Mapper<T>& map, const std::string& str) {
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(str.c_str(), root);
  if (parsingSuccessful) {
    Json::Value item = root["items"]["item"];
    Json::ArrayIndex size = item.size();
    for (Json::ArrayIndex i = 0; i != size; ++i) {
      map.start_item();
      Json::Value prop = item[i]["property"];
      for (Json::ArrayIndex j = 0; j != prop.size(); ++j) {
        map.set_property(prop[j]);
      }
    }
  }
}

};

#endif //__MAPPER_H__