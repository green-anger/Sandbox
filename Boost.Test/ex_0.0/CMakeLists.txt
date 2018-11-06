set( exe ex_0.0 )

add_executable( ${exe} main.cpp )

include_directories(
    ${Boost_INCLUDE_DIRS}
)
