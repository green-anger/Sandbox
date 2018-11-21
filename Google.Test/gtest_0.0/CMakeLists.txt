set( exe gtest_0.0 )

add_executable( ${exe} main.cpp )
target_link_libraries( ${exe} gtest_main )
