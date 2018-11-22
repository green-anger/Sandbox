set( exe catch_0.0 )

add_executable( ${exe} main.cpp )
target_link_libraries( ${exe} Catch2::Catch2 )
