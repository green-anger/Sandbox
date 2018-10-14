cmake_minimum_required( VERSION 3.0 )
project( Sandbox )

set( CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_STANDARD_REQUIRED ON )
if ( MSVC )
    add_compile_options( "/std:c++14" )
else()
    add_compile_options( -std=c++14 )
endif()

option( BUILD_EXAMPLES_OPENGL OFF )

if ( ${BUILD_EXAMPLES_OPENGL} )
    add_subdirectory( OpenGL )
endif()
