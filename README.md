# [Labs64 NetLicensing](http://netlicensing.io) Client (C++)

C++ wrapper for Labs64 NetLicensing [RESTful API](http://l64.cc/nl10)

Visit Labs64 NetLicensing at http://netlicensing.io

## Dependencies

1. [curl](https://github.com/curl/curl)
2. [jsoncpp](https://github.com/open-source-parsers/jsoncpp)(included)

## Windows build

### Build curl
1. Download curl from https://github.com/curl/curl/releases
2. cd curl_directory\winbuild
3. Read BUILD_WINDOWS.txt for building instructions
4. In VC command prompt run command like nmake /f Makefile.vc VC=your_vc MACHINE=your_machine ENABLE_WINSSL=yes
5. curl builds will be in sub directory \builds

### Build NetLicensing C++ client
1. Checkout project
2. In NetLicensingClient-cpp create build directory
3. Setup curl home directory for example using CMAKE_PREFIX_PATH=your_curl_build_directory. Build directory contains bin, include and lib subdirs.
3. In VC command prompt cd NetLicensingClient-cpp\build and issue cmake .. . To generate VC2015/x64 solution use cmake .. -G""Visual Studio 14 Win64" 
2. Open solution in VC and build library and demo client.

## Linux build

### Build NetLincesing-cpp
1. Install curl dev. For ubuntu sudo apt-get install libcurl4-openssl-dev
2. Checkout NetLicensingClient-cpp
3. Run cmake or cmake .. from build sub directory
4. make

### Unit tests

For unit tests you need installed boost unit test library. To build project with unit tests activated use cmake option -DBUILD_TESTS=yes. For example cmake -DBUILD_TESTS=yes .. . Run tests exactly from tests directory in linux or tests/Debug on windows because of expected positions of json source files.

