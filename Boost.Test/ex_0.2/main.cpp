#define BOOST_TEST_MODULE Test_0.2
#include <boost/test/included/unit_test.hpp>


struct Fixt
{
    int i;

    Fixt() : i( 0 ) { BOOST_TEST_MESSAGE( "implicit setup" );  }
    ~Fixt() { BOOST_TEST_MESSAGE( "implicit teardown" );  }
};


BOOST_AUTO_TEST_CASE( test01 )
{
    Fixt f;
    std::cout << "test01: " << f.i << std::endl;
}


BOOST_AUTO_TEST_CASE( test02 )
{
    Fixt f;
    f.i = 2;
    std::cout << "test02: " << f.i << std::endl;
}


BOOST_FIXTURE_TEST_CASE( test03, Fixt )
{
    BOOST_TEST( i == 1 );
    ++i;
}


BOOST_FIXTURE_TEST_CASE( test04, Fixt )
{
    BOOST_CHECK_EQUAL( i, 1 );
}


BOOST_FIXTURE_TEST_CASE( test05, Fixt )
{
    ++i;
    BOOST_TEST( i == 1 );
}


BOOST_FIXTURE_TEST_SUITE( suite1, Fixt )

BOOST_AUTO_TEST_CASE( test01 )
{
    BOOST_TEST_MESSAGE( "test01" );
    BOOST_TEST( i == 0 );
}

BOOST_AUTO_TEST_CASE( test02 )
{
    BOOST_TEST_MESSAGE( "test02" );
    BOOST_TEST( i == 1 );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( suite2, * boost::unit_test::fixture<Fixt>() )

BOOST_AUTO_TEST_CASE( test01 )
{
    BOOST_TEST_MESSAGE( "test01" );
    //BOOST_TEST( i == 0 );     // Cannot access fixture members
}

BOOST_AUTO_TEST_CASE( test02 )
{
    BOOST_TEST_MESSAGE( "test02" );
    //BOOST_TEST( i == 0 );     // Cannot access fixture members
}

BOOST_AUTO_TEST_SUITE_END()


struct GlobFixt
{
    static int gi;

    GlobFixt() { BOOST_TEST_MESSAGE( "global implicit setup" << gi );  }
    ~GlobFixt() { BOOST_TEST_MESSAGE( "global implicit teardown" << gi );  }
};

int GlobFixt::gi = 0;

BOOST_TEST_GLOBAL_FIXTURE( GlobFixt );

BOOST_AUTO_TEST_CASE( gtest01 )
{
    BOOST_TEST_MESSAGE( "gtest01" );
    BOOST_TEST( GlobFixt::gi == 0 );
    GlobFixt::gi = 1;
}

BOOST_AUTO_TEST_CASE( gtest02 )
{
    BOOST_TEST_MESSAGE( "gtest02" );
    BOOST_TEST( GlobFixt::gi == 1 );
}
