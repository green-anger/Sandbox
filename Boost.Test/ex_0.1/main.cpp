#define BOOST_TEST_MODULE Test_0.1
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <ctime>


namespace bdata = boost::unit_test::data;


class PlusOne
{
public:
    using sample = int;
    enum { arity = 1 };

    struct iterator
    {
        iterator() : res( 0 ) {}

        int operator*() const
        {
            return res;
        }

        void operator++()
        {
            ++res;
        }
    private:
        int res;    // current value
    };

    PlusOne() {}

    bdata::size_t size() const
    {
        return bdata::BOOST_TEST_DS_INFINITE_SIZE;
    }

    iterator begin() const
    {
        return iterator();
    }
};


namespace boost {
namespace unit_test {
namespace data {
namespace monomorphic {
    template<>
    struct is_dataset<PlusOne> : boost::mpl::true_ {};
}}}}


BOOST_DATA_TEST_CASE(
    test01,
    PlusOne() ^ bdata::make( { 0, 1, 2, 3, 5, 5, 6, 6, 8, 9 } ),
    plus_one_sample, provided )
{
    BOOST_TEST( plus_one_sample == provided );
}


BOOST_DATA_TEST_CASE( test02, bdata::xrange( 1, 4 ), var )
{
    std::cout << var << std::endl;
    BOOST_TEST( ( 1 <= var && var <= 2 ) );
}


BOOST_DATA_TEST_CASE( test03, bdata::xrange( 1, 4 ) ^ bdata::xrange( 7, 10 ), var1, var2 )
{
    std::cout << var1 << ":" << var2 << std::endl;
}


BOOST_DATA_TEST_CASE( test04,
    bdata::random(1, 17) ^ bdata::xrange( 7 ),
    rand, ind )
{
    std::cout << "test04: " << rand << ":" << ind << std::endl;
    BOOST_TEST( ( 1 <= rand && rand <= 17 ) );
}


BOOST_DATA_TEST_CASE( test05,
    bdata::random( ( bdata::distribution=std::uniform_real_distribution<float>( 1, 2 ), bdata::seed=std::time( nullptr ) ) )
    ^ bdata::xrange( 7 ),
    rand, ind )
{
    std::cout << "test05: " << rand << ":" << ind << std::endl;
    BOOST_TEST( rand < 1.7 );   // should produce ~30% of failures
}
