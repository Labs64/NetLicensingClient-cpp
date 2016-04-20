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
    for (Json::ArrayIndex i = 0; i != items_count; ++i) {
      observer.start_item();
      Json::Value properties = item[i]["property"];
      traverse(observer, properties);
      Json::Value list = item[i]["list"];
      traverse(observer, list);
      observer.end_item();
    }
  }
}

template<class Observer>
void traverse(Observer& observer, const Json::Value& root) {
  if (root.isNull()) return;
  if (!root.isArray()) return;  // TODO(a-pavlov) throw exception here
  for (Json::ValueConstIterator itr = root.begin(); itr != root.end(); ++itr) {
    observer.add_value(((*itr)["name"]).asString(), ((*itr)["value"]).asString());
  }
}

}


#endif //__TRAVERSAL_H__
