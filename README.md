<a href="https://netlicensing.io"><img src="https://netlicensing.io/img/netlicensing-stage-twitter.jpg" alt="Innovative License Management Solution"></a>

# [Labs64 NetLicensing](https://netlicensing.io) Client (C++)

[![Build Status](https://travis-ci.org/Labs64/NetLicensingClient-cpp.svg?branch=master)](https://travis-ci.org/Labs64/NetLicensingClient-cpp)

C++ wrapper for Labs64 NetLicensing [RESTful API](https://netlicensing.io/wiki/restful-api)

Visit Labs64 NetLicensing at https://netlicensing.io

## Dependencies
1. C++11 STL
2. [libcurl](https://github.com/curl/curl) (with libcurl's transitive dependencies)
3. [jsoncpp](https://github.com/open-source-parsers/jsoncpp) (included)

## Compatibility

### Notes:
- Building **NetLicensing C++ client library** with static linking is currently not supported, feel free to contribute.
- Builds verified with **libcurl** version 7.64.0 and **cmake** version 3.13.4.

### Verified builds:

Platform | Build toolset
------------ | -------------
Windows 7 | Visual studio 14 2015 x86 - x64
Windows 7 | Visual studio 15 2017 x86 - x64
Windows 10 | Visual studio 14 2015 x86 - x64
Windows 10 | Visual studio 15 2017 x86 - x64
macOS Mojave | Xcode 10.1

## Windows build

### Build curl
1. Download <b>curl</b> from https://github.com/curl/curl/releases
2. `cd curl_directory\winbuild`
3. Read `BUILD_WINDOWS.txt` for building instructions
4. In **VC command prompt** execute:
   ```
   nmake /f Makefile.vc VC=15 MACHINE=x64 ENABLE_WINSSL=yes MODE=dll
   ```
   (replace `VC` and `MACHINE` with your actual version / platform)
5. If you get the error `U1073` or `U1077` - execute `curl_directory\buildconf.bat` first and repeat the `nmake` command
6. Your `curl` build directory will be in sub directory `builds\`

### Build NetLicensing C++ client
1. Download the latest release and unpack to `NetLicensingClient-cpp` (or checkout [master](https://github.com/Labs64/NetLicensingClient-cpp.git) to build the latest development version)
2. In the `NetLicensingClient-cpp` directory create `build\` subdirectory
3. Specify **curl** location using `CMAKE_PREFIX_PATH=your_curl_build_directory`. **curl** build directory must contain `bin`, `include`, and `lib` subdirs.
4. In **VC command prompt** execute:
   ```
    cd NetLicensingClient-cpp\build
    cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH=your_curl_build_directory
   ```
   (replace `-G` argument with your actual version / platform, see [`cmake` documentation](https://cmake.org/cmake/help/latest/))
5. Open solution created in `NetLicensingClient-cpp\build` directory in Visual Studio and build the library and demo client.

## Linux build

### Build NetLincesing-cpp
1. Download the latest release and unpack to `NetLicensingClient-cpp` (or checkout [master](https://github.com/Labs64/NetLicensingClient-cpp.git) to build the latest development version)
2. Install **curl** (for development, including C headers and libraries). E.g. in **Ubuntu**:
    ```sudo apt-get install libcurl4-openssl```
3. In the `NetLicensingClient-cpp` directory create `build/` subdirectory
4. Execute:
   ```
    cd NetLicensingClient-cpp/build
    cmake ..
    make
   ```

### Unit tests

Unit tests require [**Boost**](https://www.boost.org) Unit Test Framework. To build project with the unit tests activated add cmake option `-DBUILD_TESTS=yes`. The tests must be executed from `tests/` subdirectory on Linux or `tests\Debug\` on Windows in order to properly locate the JSON files with test data.


## Execution environment

**libcurl** dynamic library should be either installed system-wide or otherwise available for the loading at run-time (typically located in the same directory as your executable)
