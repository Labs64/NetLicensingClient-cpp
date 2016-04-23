#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include "netlicensing/context.h"

BOOST_AUTO_TEST_SUITE(test_context)

BOOST_AUTO_TEST_CASE(test_params_to_query) {
  using netlicensing::url_with_parameters;
  BOOST_CHECK_EQUAL("http:///xxx/v/", url_with_parameters("http:///xxx/v/", netlicensing::Context::parameters_type()));
  BOOST_CHECK_EQUAL("http:///xxx/vvvv", url_with_parameters("http:///xxx/vvvv", netlicensing::Context::parameters_type()));

  netlicensing::Context::parameters_type params;
  params.push_back(std::make_pair("k1", "p1"));
  BOOST_CHECK_EQUAL("http://host?k1=p1", url_with_parameters("http://host", params));
  params.push_back(std::make_pair("k2", "p2"));
  BOOST_CHECK_EQUAL("http://host?k1=p1&k2=p2", url_with_parameters("http://host", params));
  BOOST_CHECK_EQUAL("https://host?k1=p1&k2=p2", url_with_parameters("https://host", params));
}

BOOST_AUTO_TEST_SUITE_END()
