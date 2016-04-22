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
  Mapper<Product> prod;
  traverse(prod, answer);
  BOOST_REQUIRE_EQUAL(1u, prod.items.size());
  BOOST_REQUIRE_EQUAL(1u, prod.items.back().discounts_.size());
  BOOST_CHECK_EQUAL("discount", prod.items.back().discounts_.back()->name_);

  BOOST_CHECK_EQUAL("101", prod.items.front().number_);
  BOOST_CHECK_EQUAL("QTPro", prod.items.front().name_);
}

BOOST_AUTO_TEST_CASE(test_product_list) {
  using namespace netlicensing;
  std::string answer = read_whole_file("product_list.json");
  BOOST_REQUIRE(!answer.empty());
  Mapper<Product> prod;
  traverse(prod, answer);
  BOOST_CHECK(!prod.items.empty());
  BOOST_CHECK(prod.items.size() > 1u);
}


BOOST_AUTO_TEST_SUITE_END()
