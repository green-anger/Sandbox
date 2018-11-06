#define BOOST_TEST_MODULE Test_0.0
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_zero )
{
    int i = 1;
    BOOST_TEST( i );
    BOOST_TEST( i == 2 );
}