set( example example_glfw )

find_package( OpenGL REQUIRED )
find_package( glm REQUIRED )
set( glfw3_include "" CACHE PATH "Path to GLFW3 include directory" )
set( glfw3_lib "" CACHE FILEPATH "Path to GLFW3 library" )

add_executable( ${example} main.cpp glad/glad.c Shader.cpp Shader.h stb_impl.cpp stb_image.h )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/glad
    ${GLM_INCLUDE_DIRS}
    ${glfw3_include}
)

target_link_libraries( ${example}
    ${OPENGL_LIBRARIES}
    ${glfw3_lib}
)

if ( WIN32 AND MSVC )
    set_target_properties( ${example} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE /ENTRY:\"mainCRTStartup\"" )
    set_target_properties( ${example} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:\"mainCRTStartup\"" )
endif()

file( COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
