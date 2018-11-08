set( exe ex_0.4 )

add_executable( ${exe} main.cpp )

include_directories(
    ${Boost_INCLUDE_DIRS}
)
