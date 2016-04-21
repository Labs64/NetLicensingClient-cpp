#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/info.h"
#include "netlicensing/traversal.h"

BOOST_AUTO_TEST_SUITE(test_licensee_validation)

BOOST_AUTO_TEST_CASE(test_plain_validation_result) {
  std::string answer = read_whole_file("../json/licensee_validation_result_plain.json");
  BOOST_REQUIRE(!answer.empty());
}

BOOST_AUTO_TEST_SUITE_END()
