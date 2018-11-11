#include <fstream>
#include <stdexcept>

#define BOOST_TEST_MODULE Test_0.5
#include <boost/test/included/unit_test.hpp>


struct Throwing
{
    int var;
    Throwing( int _var ) : var( _var )
    {
        if ( var < 0 )
        {
            throw std::runtime_error( "Negative value!" );
        }
    }
};


BOOST_AUTO_TEST_CASE( test01 )
{
    Throwing( -2 );
}


BOOST_AUTO_TEST_CASE( test02 )
{
    Throwing( 42 );
}


class File
{
public:
    File( const std::string& fileName ) : isOk_( false ), stream_( fileName )
    {
        if ( !stream_.is_open() )
        {
            throw std::runtime_error( "Cannot open file" );
        }
    }

    bool process()
    {
        return isOk_ = true;
    }

    std::map<std::string, std::size_t> result() const
    {
        if ( !isOk_ )
        {
            throw std::runtime_error( "File has not been processed" );
        }

        return map_;
    }

private:
    bool isOk_;
    std::ifstream stream_;
    std::map<std::string, std::size_t> map_;
};


BOOST_AUTO_TEST_CASE( test03 )
{
    BOOST_REQUIRE_NO_THROW( File( __FILE__ ) );
    BOOST_CHECK_THROW( File( ".." __FILE__ ), std::exception );

    {
        File file( __FILE__ );
        BOOST_CHECK_THROW( file.process(), std::logic_error );
    }
}


namespace utf = boost::unit_test;


BOOST_AUTO_TEST_CASE( test04, * utf::timeout( 2 ) )
{
    // Doesn't work on Windows
#ifdef BOOST_SIGACTION_BASED_SIGNAL_HANDLING
    while ( true ) {}
    BOOST_TEST( true );
#else
    BOOST_TEST( true );
#endif // BOOST_SIGACTION_BASED_SIGNAL_HANDLING
}