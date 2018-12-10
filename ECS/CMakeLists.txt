set( example ecs )

add_executable( ${example} main.cpp MemPool.hpp Profiler.cpp Profiler.h )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# target_link_libraries( ${example} )
