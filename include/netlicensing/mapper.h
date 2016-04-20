#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <string>
#include <list>
#include <json/json.h>

#include "netlicensing/product.h"

namespace netlicensing {

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
  if (elem["name"] == "number") items.back().number_ = elem["value"].asString();
  if (elem["name"] == "name") items.back().name_ = elem["value"].asString();
  //if (elem["name"] == "licenseeAutoCreate") items.back().lic_auto_create_ = elem["value"].asBool();
  //if (elem["name"] == "inUse") items.back().in_use_ = elem["value"].asBool();
}

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