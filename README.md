# [Labs64 NetLicensing](http://netlicensing.io) Client (C++)

C++ wrapper for Labs64 NetLicensing [RESTful API](http://l64.cc/nl10)

Visit Labs64 NetLicensing at http://netlicensing.io

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
