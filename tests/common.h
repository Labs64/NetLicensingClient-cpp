#ifndef __COMMON_H__
#define __COMMON_H__

#include <fstream>
#include <streambuf>
#include <string>

inline std::string read_whole_file(const std::string filename) {
  std::string prefix;
#ifdef WIN32
  prefix = "../json/";
#else
  prefix = "json/";
#endif

  std::ifstream t(prefix + filename);
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  return str;
}

#endif //__COMMON_H__
