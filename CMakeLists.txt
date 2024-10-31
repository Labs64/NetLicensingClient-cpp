cmake_minimum_required(VERSION 3.20)
project(netlicensing)

option (BUILD_TESTS "Build unit tests." FALSE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#find_package(JsonCpp REQUIRED)
find_package(CURL REQUIRED)

if (BUILD_TESTS)
    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost 1.40 REQUIRED unit_test_framework)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

set(LIBS ${LIBS} ${CURL_LIBRARIES} ${JSONCPP_LIBRARIES})

set(BUILD_SHARED_LIBS OFF)

add_definitions(-DCURL_STATICLIB)
if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

# enumerate header and source files for library
file(GLOB headers include/netlicensing/*.h)
source_group(include FILES ${headers})
file(GLOB sources src/*.cc)

add_library(netlicensing ${headers} ${sources})
target_link_libraries(netlicensing ${LIBS})

# client demo
file(GLOB client_demo_headers client_demo/*h)
file(GLOB client_demo_sources client_demo/*cc)
add_executable(netlicensing-client-demo ${client_demo_headers} ${client_demo_sources})
target_link_libraries(netlicensing-client-demo netlicensing ${LIBS})

if (BUILD_TESTS)
    include_directories(${Boost_INCLUDE_DIR} )
    link_directories(${Boost_LIBRARY_DIRS})
    set(test_dir "${PROJECT_SOURCE_DIR}/tests")
    file(GLOB_RECURSE test_headers ${test_dir}/*h)
    file(GLOB_RECURSE test_sources ${test_dir}/*cc)
    add_executable(run_tests ${headers} ${test_headers} ${test_sources})
    set_target_properties(run_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${test_dir})
    target_link_libraries(run_tests netlicensing ${LIBS})
    TARGET_LINK_LIBRARIES(run_tests ${Boost_LIBRARIES})
endif()

