add_executable( ecs_ex_01 main.cpp )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( ecs_ex_01 profiler mem_pool )
