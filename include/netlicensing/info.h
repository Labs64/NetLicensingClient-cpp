#ifndef __INFO_H__
#define __INFO_H__

#include <string>

namespace netlicensing {

struct Info {
  std::string value_;
  std::string id_;
  std::string type_;

  void add_property(const std::string& name, const std::string& value);
  std::string to_string() const;
};

}

#endif //__INFO_H__
