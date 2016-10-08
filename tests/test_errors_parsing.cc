#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <cassert>
#include <boost/test/unit_test.hpp>
#include "common.h"

#include "netlicensing/entity.h"
#include "netlicensing/info.h"
#include "netlicensing/mapper.h"
#include "netlicensing/traversal.h"

using netlicensing::Info;
using netlicensing::ItemWrapper;
using netlicensing::MapperBase;

struct TestInfoMapper : public MapperBase {
  ItemWrapper::Ptr_t createItem(const std::string& type) { return ItemWrapper::Ptr_t(); }
  void addItem(const ItemWrapper::Ptr_t&) {}
};

BOOST_AUTO_TEST_SUITE(test_errors_parsing)

BOOST_AUTO_TEST_CASE(test_licensee_not_found) {
  std::string answer = read_whole_file("licensee_validate_failed.json");
  BOOST_REQUIRE(!answer.empty());
  TestInfoMapper mapper;
  netlicensing::traverse(mapper, answer);
  BOOST_REQUIRE_EQUAL(1u, mapper.getInfos().size());
  BOOST_CHECK_EQUAL("Requested licensee does not exist and the productNumber is not provided", mapper.getInfos().back().getValue());
  BOOST_CHECK_EQUAL("NotFoundException", mapper.getInfos().back().getId());
  BOOST_CHECK_EQUAL("ERROR", mapper.getInfos().back().getType());
}

BOOST_AUTO_TEST_CASE(test_successfull_answer) {
  std::string answer = read_whole_file("product.json");
  BOOST_REQUIRE(!answer.empty());
  TestInfoMapper mapper;
  netlicensing::traverse(mapper, answer);
  BOOST_CHECK(mapper.getInfos().empty());
}

BOOST_AUTO_TEST_SUITE_END()
