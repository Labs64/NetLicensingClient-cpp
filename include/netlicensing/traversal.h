#ifndef __TRAVERSAL_H__
#define __TRAVERSAL_H__

#include <json/json.h>
#include <string>

namespace netlicensing {

/**
*  experemental traverser over json in predefined format
*/
template<class Observer>
void traverse(Observer& observer, const std::string& source) {
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(source.c_str(), root);
  if (parsingSuccessful) {
    Json::Value item = root["items"]["item"];
    Json::ArrayIndex items_count = item.size();
    // traverse over top level array
    for (Json::ArrayIndex i = 0; i != items_count; ++i) {
      traverse(observer, item[i], "item");      
    }
  }
}

template<class Observer>
void traverse(Observer& observer, const Json::Value& root, const std::string& name) {
  assert(!root.isNull());
  observer.start_item(name);

  // extract properties from current item
  Json::Value prop = root["property"];
  for (Json::ValueConstIterator itr = prop.begin(); itr != prop.end(); ++itr) {
    observer.add_property(((*itr)["name"]).asString(), ((*itr)["value"]).asString());
  }

  // unwind list in recursive manner
  Json::Value lists = root["list"];
  if (!lists.isNull()) {
    for (Json::ArrayIndex list_index = 0; list_index != lists.size(); ++list_index) {
      traverse(observer, lists[list_index], "list");
    }
  }

  observer.end_item();
}

}


#endif //__TRAVERSAL_H__
