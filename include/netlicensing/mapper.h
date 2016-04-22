#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <string>
#include <list>
#include <json/json.h>

#include "netlicensing/product.h"
#include "netlicensing/validation_result.h"

namespace netlicensing {

/**
* @brief internal service class for proxing traverse callbacks to items and lists hierarchy
*
*/
template<class Result>
class Mapper {
 public:
  typedef typename Result::PropertyType PropertyType;
  std::list<Result> items;
  std::deque<std::shared_ptr<PropertyType> >  properties_stack_;
  std::list<Info> info_;
  int level_;

  Mapper() : level_(0) {}

  std::string root_name() const { return "items";  }

  void begin_info() {
    info_.push_back(Info());
  }

  void add_info_property(const std::string& name, const std::string& value) {
    assert(!info_.empty());
    info_.back().add_property(name, value);
  }

  /**
  * @brief start new element - item or list
  * and make it current
  *
  */
  void begin_element(const std::string& name, const std::pair<std::string, std::string>& parameter) {
    if (name == "item") {
      assert(properties_stack_.empty());
      assert(level_ == 0);
      items.push_back(Result());
      // check type here
    }
    else {
      std::shared_ptr<PropertyType> prop(new PropertyType());
      prop->add_property(parameter.first, parameter.second);

      if (properties_stack_.empty()) {
        items.back().add_list(prop);
      }
      else {
        properties_stack_.front()->add_list(prop);
      }

      properties_stack_.push_front(prop);
    }

    ++level_;
  }

  /**
  * @brief end current element
  *
  */
  void end_element() {
    if (!properties_stack_.empty()) properties_stack_.pop_front();
    --level_;
  }

  /**
  * @brief fill properties in current element
  *
  */
  void add_property(const std::string& name, const std::string& value) {
    if (properties_stack_.empty()) {      
      items.back().add_property(name, value);
    }
    else {
      properties_stack_.front()->add_property(name, value);
    }
  }
};

};

#endif //__MAPPER_H__