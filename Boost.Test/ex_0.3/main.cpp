#define BOOST_TEST_MODULE Test_0.3
#include <boost/test/included/unit_test.hpp>


namespace utf = boost::unit_test;


BOOST_AUTO_TEST_CASE( test03, * utf::depends_on( "suite1/test01" ) )
{
    BOOST_TEST( false );
}


BOOST_AUTO_TEST_CASE( test04, * utf::depends_on( "test03" ) )
{
    BOOST_TEST( false );
}


BOOST_AUTO_TEST_CASE( test05, * utf::depends_on( "suite1/test02" ) )
{
    BOOST_TEST( false );
}



BOOST_AUTO_TEST_SUITE( suite1 )


BOOST_AUTO_TEST_CASE( test01 )
{
    BOOST_TEST( true );
}


BOOST_AUTO_TEST_CASE( test02, * utf::disabled() )
{
    BOOST_TEST( false );
}


BOOST_AUTO_TEST_SUITE_END()