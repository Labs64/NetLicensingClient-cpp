#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/mapper.h"
#include "netlicensing/validation_result.h"
#include "netlicensing/traversal.h"

BOOST_AUTO_TEST_SUITE(test_licensee_validation)

BOOST_AUTO_TEST_CASE(test_plain_validation_result) {
  using namespace netlicensing;
  std::string answer = read_whole_file("licensee_validation_result_plain.json");
  BOOST_REQUIRE(!answer.empty());
  ValidationResult vr;
  ValidationResultMapper mvr(vr);
  traverse(mvr, answer);
  BOOST_REQUIRE_EQUAL(2u, vr.getValidations().size());
  //BOOST_CHECK_EQUAL(2u, vr.getProperties().size());
  BOOST_CHECK_EQUAL("MM3M9XN63", *vr.getValidations().begin()->second.get("productModuleNumber"));
}

BOOST_AUTO_TEST_CASE(test_recursive_validation_result) {
  using namespace netlicensing;
  std::string answer = read_whole_file("licensee_validation_result_recursive.json");
  BOOST_REQUIRE(!answer.empty());
  ValidationResult vr;
  ValidationResultMapper mvr(vr);
  traverse(mvr, answer);
  BOOST_REQUIRE_EQUAL(1u, vr.getValidations().size());
  //BOOST_CHECK_EQUAL(2u, vr.getValidations().back().getProperties().size());
  //BOOST_CHECK_EQUAL(2u, vr.getValidations().back().getProperties().front()->nested_lists_.size());
  BOOST_CHECK_EQUAL("M5-DEMO", *vr.getValidations().begin()->second.get("productModuleNumber"));
}

BOOST_AUTO_TEST_SUITE_END()
