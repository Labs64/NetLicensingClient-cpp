#include "netlicensing/mapper.h"
#include "netlicensing/product.h"

#include <json/json.h>
#include <stdexcept>

namespace netlicensing {

template<>
void fromJson<Product>(Product& p, const std::string& str) {  
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(str.c_str(), root);
  if (parsingSuccessful) {
    Json::Value item = root["items"]["item"];
    Json::ArrayIndex size = item.size();
    for (Json::ArrayIndex i = 0; i != size; ++i) {
      Json::Value prop = item[i]["property"];
      for (Json::ArrayIndex j = 0; j != prop.size(); ++j) {
        if (prop[j]["name"].asString() == "name") {
          p.name_ = prop[j]["value"].asString();
        }
        else if (prop[j]["name"].asString() == "number") {
          p.number_ = prop[j]["value"].asString();
        }
      }
    }
  }
}


}
