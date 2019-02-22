<a href="https://netlicensing.io"><img src="https://netlicensing.io/img/netlicensing-stage-twitter.jpg" alt="Innovative License Management Solution"></a>

# [Labs64 NetLicensing](https://netlicensing.io) Client (C++)

[![Build Status](https://travis-ci.org/Labs64/NetLicensingClient-cpp.svg?branch=master)](https://travis-ci.org/Labs64/NetLicensingClient-cpp)

C++ wrapper for Labs64 NetLicensing [RESTful API](http://l64.cc/nl10)

Visit Labs64 NetLicensing at https://netlicensing.io

## Dependencies
1. Standard C++ (v.11 and above) and C libraries.
2. [curl](https://github.com/curl/curl) (include all transitive dependency)
3. [jsoncpp](https://github.com/open-source-parsers/jsoncpp)(included)

## Compatibility

Building <b>NetLicensing C++ client library</b> with static linking is not supported.

Platform | Build toolset | Supported
------------ | ------------- | -------------
Windows 7 | Visual studio 14 2015 x86 - x64 | [x]
Windows 7 | Visual studio 15 2017 x86 - x64 | [x]
Windows 10 | Visual studio 14 2015 x86 - x64 | [x] 
Windows 10 | Visual studio 15 2017 x86 - x64| [x]
macOS Mojave | Xcode 10.1 | [x]

## Windows build

### Build curl
1. Download <b>curl</b> from https://github.com/curl/curl/releases
2. <code>cd curl_directory\winbuild</code>
3. Read <code>BUILD_WINDOWS.txt</code> for building instructions
4. In <b>VC command prompt:</b>
    <pre>
        <code>
    nmake /f Makefile.vc VC=&#60;VC versions&#62; MACHINE=&#60;x86 or x64&#62; ENABLE_WINSSL=<b>yes</b> MODE=<b>dll</b>
        </code>
    </pre>
5. If you get the error <code>U1073</code> or <code>U1077</code> - execute <code>curl_directory\buildconf.bat</code> first and repeat command
6. Your <b>curl</b> build directory will be in sub directory <code>\builds</code>

### Build NetLicensing C++ client
1. Download latest release and unpack to <code>NetLicensingClient-cpp</code> (checkout muster if you want to build latest development version)
2. In <code>NetLicensingClient-cpp</code> create <code>build</code> directory
3. Specify <b>curl</b> <code>build</code> directory using <code>CMAKE_PREFIX_PATH=your_curl_build_directory</code>. Build directory contains <code>bin, include, lib</code> subdirs.
4. In <b>VC command prompt:</b>

    <pre>
        <code>
    cd NetLicensingClient-cpp\build
    cmake .. -G "Visual Studio <VC versions> Win&#60;86 or 64&#62;" -DCMAKE_PREFIX_PATH=your_curl_build_directory
        </code>
    </pre>
5. Open solution from <code>NetLicensingClient-cpp\build</code> directory in VC and build library and demo client.

## Linux build

### Build NetLincesing-cpp
1. Download latest release and unpack to <code>NetLicensingClient-cpp</code> (checkout muster if you want to build latest development version)
2. Install <b>curl</b> dev. For <b>Ubuntu:</b>
    <pre><code>sudo apt-get install libcurl4-openssl</code></pre>
3. In <code>NetLicensingClient-cpp</code> create <code>build</code> directory
3. Run <code>cmake ..</code> from <code>build</code> directory
4. Run <code>make</code>

### Unit tests

For unit tests you need installed <b>boost</b> unit test library. To build project with unit tests activated use cmake option <code>-DBUILD_TESTS=yes</code>. For example <code>cmake -DBUILD_TESTS=yes ..</code> . Run tests from <code>tests</code> directory on Linux or <code>tests/Debug</code> on Windows because of expected locations of json source files.


## Note

The <b>curl</b> dynamic library should be installed either system-wide or placed along with your executable file.

