#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#define BOOST_TEST_MODULE Main

#include <string>
#include <fstream>
#include <streambuf>
#include <boost/test/unit_test.hpp>
#include <json/json.h>

#include "netlicensing/product.h"
#include "netlicensing/mapper.h"
#include "netlicensing/traversal.h"

class TestObserver {
 public:
   std::string name_;
   std::string number_;

   void start_item() {

   }

   void end_item() {

   }

   void add_value(const std::string& name, const std::string& value) {
     if (name == "name") name_ = value;
     if (name == "number") number_ = value;
   }
};

BOOST_AUTO_TEST_SUITE(test_mapper)

BOOST_AUTO_TEST_CASE(initial_test) {
  std::ifstream t("../product.json");
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  BOOST_REQUIRE(!str.empty());
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(str.c_str(), root);     //parse process
  BOOST_CHECK(parsingSuccessful);
  BOOST_CHECK(root["items"]["item"].isArray());
  BOOST_CHECK_EQUAL(1u, root["items"]["item"].size());
}

BOOST_AUTO_TEST_CASE(test_trivial_product_mapper) {
  std::ifstream t("../product.json");
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  BOOST_REQUIRE(!str.empty());
  netlicensing::Product p;
  netlicensing::fromJson<netlicensing::Product>(p, str);
  BOOST_CHECK_EQUAL("101", p.number_);
  BOOST_CHECK_EQUAL("QTPro", p.name_);
}

BOOST_AUTO_TEST_CASE(test_trivial_mapper) {
  std::ifstream t("../product.json");
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  BOOST_REQUIRE(!str.empty());
  using netlicensing::Mapper;
  using netlicensing::Product;
  Mapper<Product> mp;
  netlicensing::json_enumerator(mp, str);
  BOOST_CHECK_EQUAL(1u, mp.items.size());
  BOOST_CHECK_EQUAL("101", mp.items.back().number_);
  BOOST_CHECK_EQUAL("QTPro", mp.items.back().name_);
  //BOOST_CHECK_EQUAL(true, mp.items.back().in_use_);
  //BOOST_CHECK_EQUAL(false, mp.items.back().lic_auto_create_);
}

BOOST_AUTO_TEST_CASE(test_traverse) {
  std::ifstream t("../product.json");
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  BOOST_REQUIRE(!str.empty());

  TestObserver observer;
  netlicensing::traverse(observer, str);
  BOOST_CHECK_EQUAL("101", observer.number_);
  BOOST_CHECK_EQUAL("QTPro", observer.name_);
}

BOOST_AUTO_TEST_SUITE_END()
