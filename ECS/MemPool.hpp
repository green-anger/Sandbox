#include <cstddef>


class MemPool
{
    using uint = unsigned int;
    using uchar = unsigned char;

public:
    MemPool()
        : numCells_( 0 )
        , cellSize_( 0 )
        , numFreeCells_( 0 )
        , numInit_( 0 )
        , memBeg_( nullptr )
        , next_( nullptr )
    {}

    ~MemPool()
    {
        DestroyPool();
    }

    void CreatePool( uint numCells, uint cellSize )
    {
        numCells_ = numCells;
        cellSize_ = cellSize;
        numFreeCells_ = numCells_;
        memBeg_ = new uchar[numCells_ * cellSize_];
        next_ = memBeg_;
    }

    void DestroyPool()
    {
        delete[] memBeg_;
        memBeg_ = nullptr;
    }

    uchar* AddrFromIndex( uint i ) const
    {
        return memBeg_ + ( i * cellSize_ );
    }

    uint IndexFromAddr( const uchar* p ) const
    {
        return static_cast<uint>( p - memBeg_ ) / cellSize_;
    }

    void* Allocate()
    {
        if ( numInit_ < numCells_ )
        {
            uint* p = reinterpret_cast<uint*>( AddrFromIndex( numInit_ ) );
            *p = ++numInit_;
        }

        void* res = nullptr;

        if ( numFreeCells_ > 0 )
        {
            res = static_cast<void*>( next_ );

            if ( --numFreeCells_ > 0 )
            {
                next_ = AddrFromIndex( *reinterpret_cast<uint*>( next_ ) );
            }
            else
            {
                next_ = nullptr;
            }
        }

        return res;
    }

    void Deallocate( void* p )
    {
        *static_cast<uint*>( p ) = next_ == nullptr ? numCells_ : IndexFromAddr( next_ );
        next_ = static_cast<uchar*>( p );
        ++numFreeCells_;
    }

private:
    uint numCells_;
    uint cellSize_;
    uint numFreeCells_;
    uint numInit_;
    uchar* memBeg_;
    uchar* next_;
};
