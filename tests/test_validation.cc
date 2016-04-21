#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/mapper.h"
#include "netlicensing/validation_result.h"
#include "netlicensing/info.h"
#include "netlicensing/traversal.h"

BOOST_AUTO_TEST_SUITE(test_licensee_validation)

BOOST_AUTO_TEST_CASE(test_plain_validation_result) {
  using namespace netlicensing;
  std::string answer = read_whole_file("../json/licensee_validation_result_plain.json");
  BOOST_REQUIRE(!answer.empty());
  Mapper<ValidationResult>  vr;
  traverse(vr, answer);
  BOOST_REQUIRE_EQUAL(1u, vr.validations.size());
  BOOST_CHECK_EQUAL(2u, vr.validations.back().properties_.size());
  BOOST_CHECK_EQUAL(0, vr.level_);
  BOOST_CHECK_EQUAL("MAAV03-DEMO", vr.validations.back().product_module_number_);
}

BOOST_AUTO_TEST_CASE(test_recursive_validation_result) {
  using namespace netlicensing;
  std::string answer = read_whole_file("../json/licensee_validation_result_recursive.json");
  BOOST_REQUIRE(!answer.empty());
  Mapper<ValidationResult>  vr;
  traverse(vr, answer);
  BOOST_REQUIRE_EQUAL(1u, vr.validations.size());
  BOOST_CHECK_EQUAL(2u, vr.validations.back().properties_.size());
  BOOST_CHECK_EQUAL(2u, vr.validations.back().properties_.front()->next_properties_.size());
  BOOST_CHECK_EQUAL(0, vr.level_);
  BOOST_CHECK_EQUAL("MAAV03-DEMO", vr.validations.back().product_module_number_);
}

BOOST_AUTO_TEST_SUITE_END()
