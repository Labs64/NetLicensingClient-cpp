#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/mapper.h"
#include "netlicensing/product.h"
#include "netlicensing/traversal.h"

BOOST_AUTO_TEST_SUITE(test_product)

BOOST_AUTO_TEST_CASE(test_product_with_discount) {
  using namespace netlicensing;
  std::string answer = read_whole_file("product.json");
  BOOST_REQUIRE(!answer.empty());
  StandardMapper<Product> prod;
  traverse(prod, answer);
  BOOST_REQUIRE_EQUAL(1u, prod.getItems().size());
  BOOST_REQUIRE_EQUAL(1u, prod.getItems().back().getDiscounts().size());
  BOOST_CHECK_EQUAL("10.00", prod.getItems().back().getDiscounts().back().getTotalPrice().toString());
  BOOST_CHECK_EQUAL("101", prod.getItems().front().getNumber().toString());
  BOOST_CHECK_EQUAL("QTPro", prod.getItems().front().getName().toString());
}

BOOST_AUTO_TEST_CASE(test_product_list) {
  using namespace netlicensing;
  std::string answer = read_whole_file("product_list.json");
  BOOST_REQUIRE(!answer.empty());
  StandardMapper<Product> prod;
  traverse(prod, answer);
  BOOST_CHECK(!prod.getItems().empty());
  BOOST_CHECK(prod.getItems().size() > 1u);
}


BOOST_AUTO_TEST_SUITE_END()
