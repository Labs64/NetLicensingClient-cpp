<a href="https://netlicensing.io"><img src="https://netlicensing.io/img/netlicensing-stage-twitter.jpg" alt="Innovative License Management Solution"></a>

# [Labs64 NetLicensing](https://netlicensing.io) Client (C++)

[![Build Status](https://travis-ci.org/Labs64/NetLicensingClient-cpp.svg?branch=master)](https://travis-ci.org/Labs64/NetLicensingClient-cpp)

C++ wrapper for Labs64 NetLicensing [RESTful API](http://l64.cc/nl10)

Visit Labs64 NetLicensing at https://netlicensing.io

## Dependencies

1. [curl](https://github.com/curl/curl)
2. [jsoncpp](https://github.com/open-source-parsers/jsoncpp)(included)

## Windows build

### Build curl
1. Download curl from https://github.com/curl/curl/releases
2. <code>cd curl_directory\winbuild</code>
3. Read <code>BUILD_WINDOWS.txt</code> for building instructions
4. In VC command prompt run command like
    <pre>
        <code>
    nmake /f Makefile.vc VC=&#60;VC versions&#62; MACHINE=&#60;x86 or x64&#62; ENABLE_WINSSL=<b>yes</b> MODE=<b>dll</b>
        </code>
    </pre>
5. If you get the error "U1073" or "U1077" - execute <code>curl_directory\buildconf.bat</code> first and repeat command
6. Your curl build directory will be in sub directory <code>\builds</code>

### Build NetLicensing C++ client
1. Checkout project
2. In NetLicensingClient-cpp create build directory
3. Setup curl home directory for example using CMAKE_PREFIX_PATH=your_curl_build_directory. Build directory contains <b>bin</b>, <b>include</b> and <b>lib</b> subdirs.
3. In VC Command prompt:

    <pre>
        <code>
    cd NetLicensingClient-cpp\build
    cmake .. -G "Visual Studio <VC versions> Win&#60;86 or 64&#62;" -DCMAKE_PREFIX_PATH=your_curl_build_directory
        </code>
    </pre>
2. Open solution from "<b>NetLicensingClient-cpp\build</b>" directory in VC and build library and demo client.


## Linux build

### Build NetLincesing-cpp
1. Install curl dev. For ubuntu sudo apt-get install libcurl4-openssl-dev
2. Checkout NetLicensingClient-cpp
3. Run cmake or cmake .. from build sub directory
4. make

### Unit tests

For unit tests you need installed boost unit test library. To build project with unit tests activated use cmake option -DBUILD_TESTS=yes. For example cmake -DBUILD_TESTS=yes .. . Run tests exactly from tests directory in linux or tests/Debug on windows because of expected positions of json source files.

