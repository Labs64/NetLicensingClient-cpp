#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <cassert>

namespace netlicensing {

struct NamedList {
  std::string name_;

  bool add_property(const std::string& name, const std::string& value) {
    if (name == "name") {
      name_ = value;
      return true;
    }

    return false;
  }
};

template<class T>
struct RecursiveList : public NamedList {
  std::list<std::shared_ptr<RecursiveList<T> > >  nested_lists_;

  void add_list(std::shared_ptr<RecursiveList<T> > ptr) {
    nested_lists_.push_back(ptr);
  }
};

template<class T>
struct FlatList : public NamedList {
  void add_list(std::shared_ptr<FlatList<T> > ptr) {
    throw std::logic_error("Flat list is not support nested levels");
  }
};

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

class Entity {
private:
  typedef std::map<std::string, std::string> user_properties_map;
  user_properties_map user_defined_properties_;
public:
  bool add_property(const std::string& key, const std::string& value);
  std::string get_property(const std::string& key) const;
  std::string to_string() const;
};

}

#endif //__ENTITY_H__