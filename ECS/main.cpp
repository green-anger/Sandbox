#include <cstdint>

#include "MemPool.hpp"
#include "Profiler.h"


int main( int argc, char** argv )
{
    MemPool mp;
    mp.CreatePool( 4, sizeof( uint32_t ) );

    uint32_t* p0 = static_cast<uint32_t*>( mp.Allocate() );
    uint32_t* p1 = static_cast<uint32_t*>( mp.Allocate() );
    uint32_t* p2 = static_cast<uint32_t*>( mp.Allocate() );
    mp.Deallocate( p0 );
    mp.Deallocate( p2 );
    uint32_t* p3 = static_cast<uint32_t*>( mp.Allocate() );
    uint32_t* p4 = static_cast<uint32_t*>( mp.Allocate() );
    uint32_t* p5 = static_cast<uint32_t*>( mp.Allocate() );
    mp.Deallocate( p1 );

    p0 = p1 = p2 = p3 = p4 = p5 = nullptr;
    mp.DestroyPool();

    const int num = 10000;
    const int size = 1000;
    const int tot = 4 * size * num;

    {
        alt::Profiler prof( "new", true );
        uint32_t* arr[size];

        for ( int n = 0; n < num; ++n )
        {
            for ( int i = size - 1; 0 <= i; --i )
            {
                arr[i] = new uint32_t;
            }

            for ( int i = size - 1; 0 <= i; --i )
            {
                delete arr[i];
            }

            for ( int i = 0; i < size; ++i )
            {
                arr[i] = new uint32_t;
            }

            for ( int i = 0; i < size; ++i )
            {
                delete arr[i];
            }
        }
    }

    {
        alt::Profiler prof( "pool", true );
        uint32_t* arr[size];
        MemPool mp;
        mp.CreatePool( size, sizeof( uint32_t ) );

        for ( int n = 0; n < num; ++n )
        {
            for ( int i = size - 1; 0 <= i; --i )
            {
                arr[i] = static_cast<uint32_t*>( mp.Allocate() );
            }

            for ( int i = size - 1; 0 <= i; --i )
            {
                mp.Deallocate( arr[i] );
            }

            for ( int i = 0; i < size; ++i )
            {
                arr[i] = static_cast<uint32_t*>( mp.Allocate() );
            }

            for ( int i = 0; i < size; ++i )
            {
                mp.Deallocate( arr[i] );
            }
        }

        mp.DestroyPool();
    }

    return 0;
}
