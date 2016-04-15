cmake_minimum_required(VERSION 2.6)
project(netlicensing)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#find_package(JsonCpp REQUIRED)
find_package(CURL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

set(LIBS ${LIBS} ${CURL_LIBRARIES}) # ${JSONCPP_LIBRARIES})

set(BUILD_SHARED_LIBS OFF)

add_definitions(-DCURL_STATICLIB)

# enumerate header and source files for library
file(GLOB headers include/netlicensing/*.h)
source_group(include FILES ${headers})
file(GLOB sources src/*.cc)

add_library(netlicensing ${headers} ${sources})
target_link_libraries(netlicensing ${LIBS})

# demo client 
file(GLOB client_demo_headers client_demo/${db2lp_component}/*h)
file(GLOB client_demo_sources client_demo/${db2lp_component}/*cc)
add_executable(netlicensing-client-demo ${client_demo_headers} ${client_demo_sources} )
target_link_libraries(netlicensing-client-demo netlicensing ${LIBS})
