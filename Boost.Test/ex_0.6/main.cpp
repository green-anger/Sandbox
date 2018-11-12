#define BOOST_TEST_MODULE Test_0.6
#include <boost/test/included/unit_test.hpp>


bool isEven( int i )
{
    return i % 2 == 0;
}


BOOST_AUTO_TEST_CASE( test01_is_even )
{
    BOOST_CHECK_PREDICATE( isEven, ( 14 ) );
    int i = 17;
    BOOST_CHECK_PREDICATE( isEven, ( i ) );
}


boost::test_tools::predicate_result
compareVecs( const std::vector<int>& v1, const std::vector<int>& v2 )
{
    if ( v1.size() != v2.size() )
    {
        boost::test_tools::predicate_result res( false );
        res.message() << "Different sizes [" << v1.size() << "!=" << v2.size() << "]";
        return res;
    }

    return true;
}


BOOST_AUTO_TEST_CASE( test02_compare_pred )
{
    std::vector<int> v1{ 1, 2 };
    std::vector<int> v2;
    BOOST_TEST( compareVecs( v1, v2 ) );
}
