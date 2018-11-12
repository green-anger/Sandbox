#define BOOST_TEST_MODULE Test_0.7
#include <boost/test/included/unit_test.hpp>

struct Processor
{
    int level;

    void optimization_level( int lvl ) { level = lvl; }
    bool op1( int ) { return level < 2; }
    bool op2( int, int ) { return level < 1; }
};


void test_operations( Processor& processor, int limit )
{
    for ( int i = 0; i < limit; ++i )
    {
        BOOST_TEST_CONTEXT( "With parameter i = " << i )
        {
            BOOST_TEST( processor.op1( i ) );
            for ( int j = 0; j < i; ++j )
            {
                BOOST_TEST_INFO( "With parameter j = " << j );
                BOOST_TEST( processor.op2( i, j ) );
            }
        }
    }
}


BOOST_AUTO_TEST_CASE( test01 )
{
    Processor processor;

    for ( int level = 0; level < 3; ++level )
    {
        BOOST_TEST_CONTEXT( "With optimization level " << level )
        {
            processor.optimization_level( level);
            test_operations( processor, 2 );
        }
    }
}
