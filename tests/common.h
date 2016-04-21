#ifndef __COMMON_H__
#define __COMMON_H__

#include <fstream>
#include <streambuf>
#include <string>

inline std::string read_whole_file(const std::string filepath) {
  std::ifstream t(filepath);
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  return str;
}

#endif //__COMMON_H__