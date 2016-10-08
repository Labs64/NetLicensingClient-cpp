#ifndef __TRAVERSAL_H__
#define __TRAVERSAL_H__

#include <json/json.h>
#include <string>

#include "netlicensing/mapper.h"

namespace netlicensing {

  inline void traverse_elements(ItemWrapper::Ptr_t& currentItem, const Json::ValueIterator& item) {
    if (!currentItem) {  // skip level if no container was provided
      return;
    }
    // extract properties from current item
    const Json::Value& props = (*item)["property"];
    for (Json::ValueIterator prop = props.begin(); prop != props.end(); ++prop) {
      currentItem->addProperty((*prop)["name"].asString(), (*prop)["value"].asString());
    }
    // unwind lists recursively
    const Json::Value& list = (*item)["list"];
    if (!list.isNull()) {
      for (Json::ValueIterator entry = list.begin(); entry != list.end(); ++entry) {
        ItemWrapper::Ptr_t nestedItem = currentItem->createNested();
        traverse_elements(nestedItem, entry);
        currentItem->addNested((*entry)["name"].asString(), nestedItem);
      }
    }
  }

  /**
  *  experemental traverser over json in predefined format
  */
  template<typename T>
  inline void traverse(T& mapper, const std::string& source) {
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(source.c_str(), root);
    if (parsingSuccessful) {
      // parse info stucture
      const Json::Value& infos = root["infos"]["info"];
      if (!infos.isNull()) {
        for (Json::ValueIterator info = infos.begin(); info != infos.end(); ++info) {
          mapper.addInfo((*info)["id"].asString(), (*info)["type"].asString(), (*info)["value"].asString());
        }
      }

      // get top level element of structure
      const Json::Value& items = root["items"]["item"];
      if (!items.isNull()) {
        for (Json::ValueIterator item = items.begin(); item != items.end(); ++item) {
          ItemWrapper::Ptr_t resultItem = mapper.createItem((*item)["type"].asString());
          traverse_elements(resultItem, item);
          mapper.addItem(resultItem);
        }
      }
    }
  }

}  // namespace netlicensing

#endif  // __TRAVERSAL_H__
