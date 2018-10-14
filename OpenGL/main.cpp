#include "glad/glad/glad.h"

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "stb_image.h"


void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mode );
std::tuple<GLFWwindow*, int, int> setupWindow( const std::string& title );


int main( int argc, char** argv )
{
    std::tuple<GLFWwindow*, int, int> tup = setupWindow( "Texture load" );
    auto window = std::get<0>( tup );

    if ( !window )
        return -1;

    if ( !gladLoadGL() )
        return -2;

    const auto width = std::get<1>( tup );
    const auto height = std::get<2>( tup );

    glfwSetKeyCallback( window, keyCallback );

    Shader shaderTexture( "shaders/texture.vs", "shaders/texture.fs" );

    if ( !shaderTexture.isValid() )
    {
        throw std::logic_error( "Shader initialization failed!" );
    }

    GLint stProj = shaderTexture.uniformLocation( "proj" );
    GLint stSample = shaderTexture.uniformLocation( "sample" );

    static const glm::mat4 view = glm::lookAt(
        glm::vec3( 0.0f, 0.0f, 10.0f ),     // position
        glm::vec3( 0.0f, 0.0f, 0.0f ),      // target
        glm::vec3( 0.0f, 1.0f, 0.0f )       // up vector
    );
    glm::mat4 proj = glm::ortho( -2.0f, 2.0f, -2.0f, 2.0f, 0.0f, 10.0f ) * view;

    GLuint vao;
    GLuint vbo;
    GLuint tex;
    GLsizei num;

    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) 0 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );

    std::vector<GLfloat> vec;
    vec.reserve( 24 );
    const GLfloat len = 1.0f;
    vec = {
        -len, -len, 0.0f, 0.0f,
        +len, -len, 1.0f, 0.0f,
        +len, +len, 1.0f, 1.0f,
        -len, -len, 0.0f, 0.0f,
        +len, +len, 1.0f, 1.0f,
        -len, +len, 0.0f, 1.0f
    };
    num = 6;

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vec.size() * sizeof( GLfloat ), &vec[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    stbi_set_flip_vertically_on_load( true );
    int w;
    int h;
    int nrChannels;
    auto buffer = stbi_load( "images/0.png", &w, &h, &nrChannels, 0 );

    glBindTexture( GL_TEXTURE_2D, tex );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer );
    glBindTexture( GL_TEXTURE_2D, 0 );
    
    stbi_image_free( buffer );

    shaderTexture.use();
    glUniformMatrix4fv( stProj, 1, GL_FALSE, glm::value_ptr( proj ) );

    while ( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents();
        
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glBindVertexArray( vao );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, tex );
        glDrawArrays( GL_TRIANGLES, 0, num );
        glBindTexture( GL_TEXTURE_2D, 0 );
        glBindVertexArray( 0 );

        glfwSwapBuffers( window );
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}


void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose( window, GLFW_TRUE );
    }
}


std::tuple<GLFWwindow*, int, int> setupWindow( const std::string& title )
{
    if ( !glfwInit() )
    {
        return std::make_tuple( nullptr, 0, 0 );
    }

    const auto width = 512;
    const auto height = 512;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_SAMPLES, 8 );

    GLFWwindow* window = glfwCreateWindow( width, height, title.c_str(), 0, 0 );
    if ( !window )
    {
        return std::make_tuple( nullptr, 0 , 0 );
    }

    glfwSetWindowPos( window, 500, 500 );
    glfwMakeContextCurrent( window );
    glfwSwapInterval( 1 );

    return std::make_tuple( window, width, height );
}
