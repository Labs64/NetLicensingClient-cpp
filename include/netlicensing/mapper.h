#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <string>
#include <list>
#include <json/json.h>
#include <sstream>

#include "netlicensing/product.h"

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