#include <sstream>
#include <vector>

#define BOOST_TEST_MODULE Test_0.4
#include <boost/test/included/unit_test.hpp>
#include <boost/rational.hpp>


namespace utf = boost::unit_test;
namespace tt = boost::test_tools;


BOOST_AUTO_TEST_CASE( test01, * utf::tolerance( 0.00001 ) )
{
    double x = 10.0000000;
    double y = 10.0000001;
    double z = 10.001;
    BOOST_TEST( x == y );
    BOOST_TEST( x == y, tt::tolerance( 0.0 ) );     // override test case tolarance

    BOOST_TEST( x == z );
    BOOST_TEST( x == z, tt::tolerance( 0.001 ) );   // override test case tolarance
}


double x = 10.000000;
double d =  0.000001;


BOOST_AUTO_TEST_CASE( test02_pass, * utf::tolerance( 0.0001 ) )
{
    BOOST_TEST( x + d == x );
    BOOST_TEST( x + d <= x );
    BOOST_TEST( d == 0.0 );
}


BOOST_AUTO_TEST_CASE( test03_fail, * utf::tolerance( 0.0001 ) )
{
    BOOST_TEST( x - d < x );
    BOOST_TEST( x - d != x );
    BOOST_TEST( d > 0.0 );
    BOOST_TEST( d < 0.0 );
}


namespace boost {
namespace math {
namespace fpc {


template<typename I>
struct tolerance_based<rational<I>> : boost::true_type {};


}}}


using ratio = boost::rational<int>;


BOOST_AUTO_TEST_CASE( test04, * utf::tolerance( ratio( 1, 1000 ) ) )
{
    ratio x( 1002, 100 );   // 10.02
    ratio y( 1001, 100 );   // 10.01
    ratio z( 1000, 100 );   // 10.00

    BOOST_TEST( x == y );
    BOOST_TEST( x == y, tt::tolerance( ratio( 1, 2000 ) ) );

    BOOST_TEST( x != z );
    BOOST_TEST( x != z, tt::tolerance( ratio( 2, 1000 ) ) );
}


BOOST_AUTO_TEST_CASE( test05 )
{
    const char* a = "str1";
    const char* b = "str2";
    const char* c = "str3";
    BOOST_TEST( a == b );
    BOOST_TEST( a == c );
    BOOST_TEST( std::string( "str1" ) == b );
    BOOST_TEST( std::string( "str1" ) < a );
    BOOST_TEST( std::string( "str1" ) < a, tt::per_element() );
    BOOST_TEST( a < b, tt::lexicographic() );
}


BOOST_AUTO_TEST_CASE( test06 )
{
    std::vector<int> a{ 1, 2, 3 };
    std::vector<int> c{ 1, 5, 3, 4 };
    std::vector<long> b{ 1, 5, 3};

    // BOOST_TEST( a == b );    // will not compile
    // BOOST_TEST( a <= b );    // will not compile

    BOOST_TEST( a < c );
    BOOST_TEST( a >= c );
    BOOST_TEST( a != c );
}


BOOST_AUTO_TEST_CASE( test07 )
{
    int a[] = { 1, 2, 3 };
    int b[] = { 1, 5, 3, 4 };
    std::vector<long> c{ 1, 5, 3, 4 };
    BOOST_TEST( a == a );
    BOOST_TEST( a == b );
    BOOST_TEST( a != b );
    BOOST_TEST( a < b );
    BOOST_TEST( b < c );
    BOOST_TEST( c < a );

    std::vector<int> v1{ 1, 2, 3 };
    std::vector<long> v2{ 1, 5, 3 };
    std::list<short> v3{ 1, 5, 3, 4 };

    BOOST_TEST( v1 == v2, tt::per_element() );
    BOOST_TEST( v1 != v2, tt::per_element() );
    BOOST_TEST( v2 < v3, tt::per_element() );
    BOOST_TEST( v2 >= v3, tt::per_element() );
    BOOST_TEST( v2 != v3, tt::per_element() );

    int ar1[] = { 1, 2, 3 };
    int ar2[] = { 1, 5, 3 };
    std::vector<long> v4{ 1, 5, 3 };

    BOOST_TEST( ar1 == ar2, tt::per_element() );
    BOOST_TEST( ar1 != ar2, tt::per_element() );
    BOOST_TEST( ar1 < ar2, tt::per_element() );
    BOOST_TEST( ar2 < v4, tt::per_element() );
    BOOST_TEST( v4 < ar1, tt::per_element() );
}


BOOST_AUTO_TEST_CASE( test08 )
{
    std::vector<int> v1{ 1, 2, 3 };
    std::vector<int> v2{ 1, 2, 2 };
    std::vector<int> v3{ 1, 2, 3, 4 };

    BOOST_TEST( v1 < v1, tt::lexicographic() );
    BOOST_TEST( v1 < v2, tt::lexicographic() );
    BOOST_TEST( v1 < v3, tt::lexicographic() );
    BOOST_TEST( v1 >= v3, tt::lexicographic() );

    int a[] = { 1, 2, 3 };
    int b[] = { 1, 5, 3 };
    std::vector<long> c{ 1, 5, 3 };

    // BOOST_TEST( a == b, tt::lexicographic() );   // will not compile
    // BOOST_TEST( a != b, tt::lexicographic() );   // will not compile
    BOOST_TEST( a < b, tt::lexicographic() );
    BOOST_TEST( b < c, tt::lexicographic() );
    BOOST_TEST( c < a, tt::lexicographic() );
}


BOOST_AUTO_TEST_CASE( test09 )
{
    int a = 0xAB;
    BOOST_TEST( a == ( a & ~1 ), tt::bitwise() );
    BOOST_TEST( a == a + 1, tt::bitwise() );
    BOOST_TEST( a != a + 1, tt::bitwise() );
    int b = 0x88;
    BOOST_TEST( a == b, tt::bitwise() );
}
