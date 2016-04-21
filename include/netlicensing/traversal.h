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
    // get top level element of structure
    Json::Value item = root[observer.root_name()];

    if (!item.isNull() && item.isObject()) {
      // TODO(a-pavlov) use something better here
      std::string staff_name = observer.root_name().substr(0, observer.root_name().length() - 1);
      Json::Value staff = item[staff_name];
      Json::ArrayIndex items_count = staff.size();
      // traverse over top level array
      for (Json::ArrayIndex i = 0; i != items_count; ++i) {
        traverse(observer, staff[i], staff_name);
      }
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

template<class Observer>
void info_traverse(Observer& observer, const std::string& source) {
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(source.c_str(), root);

  if (parsingSuccessful) {
    // get top level element of structure
    Json::Value item = root[observer.root_name()];

    if (!item.isNull() && item.isObject()) {
      // TODO(a-pavlov) use something better here
      std::string staff_name = observer.root_name().substr(0, observer.root_name().length() - 1);
      Json::Value staff = item[staff_name];
      for (Json::ValueConstIterator itr = staff.begin(); itr != staff.end(); ++itr) {
        observer.start_item(staff_name);
        std::vector<std::string> v = itr->getMemberNames();
        for (std::vector<std::string>::const_iterator nm = v.begin(); nm != v.end(); ++nm) {
          observer.add_property(*nm, ((*itr)[*nm]).asString());
        }

        observer.end_item();
      }
    }
  }
}

}


#endif //__TRAVERSAL_H__
