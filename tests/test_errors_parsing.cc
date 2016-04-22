#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/entity.h"
#include "netlicensing/traversal.h"

using netlicensing::Info;

struct TestInfoObserver {
  std::list<Info> infos_;
  std::string root_name() const { return "infos";  }
  void begin_info() {
    infos_.push_back(Info());
  }

  void begin_element(const std::string&, const std::pair<std::string, std::string>&) {}
  void end_element() {}
  void add_property(const std::string&, const std::string&) {}



  void add_info_property(const std::string& name, const std::string& value) {
    infos_.back().add_property(name, value);
  }
};

BOOST_AUTO_TEST_SUITE(test_errors_parsing)

BOOST_AUTO_TEST_CASE(test_licensee_not_found) {
  std::string answer = read_whole_file("licensee_validate_failed.json");
  BOOST_REQUIRE(!answer.empty());
  TestInfoObserver observer;
  netlicensing::traverse(observer, answer);
  BOOST_REQUIRE_EQUAL(1u, observer.infos_.size());
  BOOST_CHECK_EQUAL("Requested licensee does not exist and the productNumber is not provided", observer.infos_.back().value_);
  BOOST_CHECK_EQUAL("NotFoundException", observer.infos_.back().id_);
  BOOST_CHECK_EQUAL("ERROR", observer.infos_.back().type_);
}

BOOST_AUTO_TEST_CASE(test_successfull_answer) {
  std::string answer = read_whole_file("product.json");
  BOOST_REQUIRE(!answer.empty());
  TestInfoObserver observer;
  netlicensing::traverse(observer, answer);
  BOOST_CHECK(observer.infos_.empty());
}

BOOST_AUTO_TEST_SUITE_END()
