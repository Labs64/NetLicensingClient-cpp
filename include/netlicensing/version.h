#ifndef __NETLICENSING_VERSION__
#define __NETLICENSING_VERSION__

#define NETLICENSING_VERSION_MAJOR 2
#define NETLICENSING_VERSION_MINOR 5
#define NETLICENSING_VERSION_TINY  0

#define NETLICENSING_VERSION "2.5.0"

// the format of this version is: MMmmtt
// M = Major version, m = minor version, t = tiny version
#define LIBED2K_VERSION_NUM ((NETLICENSING_VERSION_MAJOR * 10000) + (NETLICENSING_VERSION_MINOR * 100) + NETLICENSING_VERSION_TINY)

#define xstr(a) str(a)
#define str(a) #a

#if defined(__linux__)
  #define NL_PLAT "Linux"
#elif defined(__APPLE__)
  #define NL_PLAT "macOS"
#elif defined(_WIN32)
  #define NL_PLAT "Windows"
#else
  #define NL_PLAT "Unknown"
#endif

#if defined(_MSC_VER)
  #define NL_CPP "MSVC"
  #define NL_CPP_VER xstr(_MSC_VER)
  #define NL_ARCH_WIN
#elif defined(__llvm__)
  #define NL_CPP "Clang"
  #define NL_CPP_VER xstr(__clang_major__.__clang_minor__.__clang_patchlevel__)
#elif defined(__GNUC__)
  #define NL_CPP "GCC"
  #define NL_CPP_VER xstr(__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__)
#elif defined(__BORLANDC__)
  #define NL_CPP "BC"
  #define NL_CPP_VER xstr(__BORLANDC__)
  #define NL_ARCH_WIN
#else
  #define NL_CPP "Unknown"
  #define NL_CPP_VER
#endif

#if defined(NL_ARCH_WIN)
  #if defined(_WIN64)
    #define NL_ARCH "64"
  #else
    #define NL_ARCH "32"
  #endif
#else
  #if defined(__x86_64__)
    #define NL_ARCH "64"
  #else
    #define NL_ARCH "32"
  #endif
#endif

#endif //__NETLICENSING_VERSION__
