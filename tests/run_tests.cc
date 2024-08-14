#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#define BOOST_TEST_MODULE Main

#ifndef _AIX
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>

#include <string>
#include <deque>
#include <json/json.h>

#include "netlicensing/product.h"
#include "netlicensing/mapper.h"
#include "netlicensing/traversal.h"

#include "common.h"

struct TestDiscount {
  std::string currency_;
};

struct TestProduct {
  std::list<TestDiscount>  discounters;
  std::string name_;
  std::string number_;
};

class TestObserver {
 public:
  std::list<TestProduct> product_;
  std::deque<std::string>  items_stack_;
  size_t max_depth;
  std::string root_name_;

  TestObserver(const std::string& root_name) : max_depth(0), root_name_(root_name) {}

  std::string root_name() const {
    return root_name_;
  }

  void start_item(const std::string& name) {
    items_stack_.push_front(name);
    if (name == "item") {
      product_.push_back(TestProduct());
    }
    else if (name == "list") {
      product_.back().discounters.push_back(TestDiscount());
    }

    ++max_depth;
  }

  void end_item() {
    items_stack_.pop_front();
  }

  void add_property(const std::string& name, const std::string& value) {
    assert(!items_stack_.empty());

    if (items_stack_.front() == "list") {
      if (name == "currency") (product_.back().discounters.back().currency_ = value);
    }
    else {
      if (name == "name") product_.back().name_ = value;
      if (name == "number") product_.back().number_ = value;
    }
  }
};

BOOST_AUTO_TEST_SUITE(test_mapper)

BOOST_AUTO_TEST_CASE(initial_test) {
  std::string str = read_whole_file("product.json");
  BOOST_REQUIRE(!str.empty());
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(str.c_str(), root);     //parse process
  BOOST_CHECK(parsingSuccessful);
  BOOST_CHECK(root["items"]["item"].isArray());
  BOOST_CHECK_EQUAL(1u, root["items"]["item"].size());
}

BOOST_AUTO_TEST_CASE(test_trivial_mapper) {
  /*
  std::string str = read_whole_file("../json/product.json");
  BOOST_REQUIRE(!str.empty());
  using netlicensing::Mapper;
  using netlicensing::Product;
  Mapper<Product> mp;
  netlicensing::json_enumerator(mp, str);
  BOOST_CHECK_EQUAL(1u, mp.items.size());
  BOOST_CHECK_EQUAL("101", mp.items.back().number_);
  BOOST_CHECK_EQUAL("QTPro", mp.items.back().name_);
  BOOST_CHECK_EQUAL(true, mp.items.back().in_use_);
  BOOST_CHECK_EQUAL(false, mp.items.back().lic_auto_create_);
  */
}

BOOST_AUTO_TEST_CASE(test_traverse) {
  /*
  std::string str = read_whole_file("../json/product.json");
  BOOST_REQUIRE(!str.empty());

  TestObserver observer("items");
  netlicensing::traverse(observer, str);
  BOOST_CHECK_EQUAL("101", observer.product_.front().number_);
  BOOST_CHECK_EQUAL("QTPro", observer.product_.front().name_);
  BOOST_CHECK_EQUAL("EUR", observer.product_.front().discounters.front().currency_);
  */
}

BOOST_AUTO_TEST_CASE(test_recursive_list) {
  /*
  std::string str = read_whole_file("../json/recursive_product.json");
  BOOST_REQUIRE(!str.empty());
  TestObserver observer("items");
  netlicensing::traverse(observer, str);
  BOOST_CHECK_EQUAL("101", observer.product_.front().number_);
  BOOST_CHECK_EQUAL("QTPro", observer.product_.front().name_);
  BOOST_CHECK_EQUAL("EUR", observer.product_.front().discounters.front().currency_);
  BOOST_CHECK_EQUAL(4u, observer.max_depth);
  BOOST_CHECK(observer.items_stack_.empty());
  */
}

BOOST_AUTO_TEST_SUITE_END()
