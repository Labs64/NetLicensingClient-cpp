#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/info.h"
#include "netlicensing/traversal.h"

using netlicensing::Info;

struct TestInfoObserver {
  std::list<Info> infos;
  std::string root_name() const { return "infos";  }
  void start_item(const std::string&) {
    infos.push_back(Info());
  }

  void end_item() {

  }

  void add_property(const std::string& name, const std::string& value) {
    assert(!infos.empty());
    if (name == "value") infos.back().value_ = value;
    else if (name == "id") infos.back().id_ = value;
    else if (name == "type") infos.back().type_ = value;
  }
};

BOOST_AUTO_TEST_SUITE(test_errors_parsing)

BOOST_AUTO_TEST_CASE(test_licensee_not_found) {
  std::string answer = read_whole_file("../json/licensee_validate_failed.json");
  BOOST_REQUIRE(!answer.empty());
  TestInfoObserver observer;
  netlicensing::info_traverse(observer, answer);
  BOOST_REQUIRE_EQUAL(1u, observer.infos.size());
  BOOST_CHECK_EQUAL("Requested licensee does not exist and the productNumber is not provided", observer.infos.back().value_);
  BOOST_CHECK_EQUAL("NotFoundException", observer.infos.back().id_);
  BOOST_CHECK_EQUAL("ERROR", observer.infos.back().type_);
}

BOOST_AUTO_TEST_CASE(test_successfull_answer) {
  std::string answer = read_whole_file("../json/product.json");
  BOOST_REQUIRE(!answer.empty());
  TestInfoObserver observer;
  netlicensing::info_traverse(observer, answer);
  BOOST_CHECK(observer.infos.empty());
}

BOOST_AUTO_TEST_SUITE_END()