set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )

find_package( Boost 1.21.0 REQUIRED )

add_subdirectory( ex_0.0 )
add_subdirectory( ex_0.1 )
add_subdirectory( ex_0.2 )
add_subdirectory( ex_0.3 )
