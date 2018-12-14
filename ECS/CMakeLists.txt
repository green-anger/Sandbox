add_library( profiler Profiler.cpp Profiler.h )
add_library( mem_pool INTERFACE )
target_include_directories( mem_pool INTERFACE MemPool.hpp )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory( ex_01 )
