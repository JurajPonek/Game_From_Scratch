
#include "auto_release.hpp"
#include "src/opengl.hpp"
#include "vendor/opengl/glext.h"
#include "window.hpp"
#include "opengl.hpp"
#include <gl/gl.h>
#include <stdexcept>
#include <string_view>

namespace  
{
    static constexpr auto vertex_shader_source = R"(
    #version 460 core
    
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 in_color;

    out vec3 out_color;
    
    void main()
    {
        gl_Position = vec4(position, 1.0);
        out_color = in_color;
    }
)";

static constexpr auto fragment_shader_source = R"(
    #version 460 core

    in vec3 out_color;
    out vec4 frag_color;
    
    void main()
    {
        frag_color = vec4(out_color, 1.0);
    }
)";
game::AutoRelease<GLuint> compile_shader(std::string_view source, ::GLenum shader_type)
{
    auto shader = game::AutoRelease<::GLuint>
    {
        ::glCreateShader(shader_type), ::glDeleteShader
    };
    const char* string[] = {source.data()};
    const ::GLint lenghts[] = {static_cast<::GLint>(source.length())};
    ::glShaderSource(shader, 1, string, lenghts);
    ::glCompileShader(shader);
    ::GLint res{};
    ::glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (!res) throw std::runtime_error("Failed to compile shader");
    return shader;
}
}






int main()
{
    game::Window window{800u, 600u};
    static constexpr float vertices[] = 
    {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,0.0f, 0.0f, 1.0f

    };
    auto vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    auto fragment_shader = compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);
    auto program = game::AutoRelease<::GLuint>
    {
        ::glCreateProgram(), ::glDeleteProgram
    };
    if (!program) throw std::runtime_error("failed to create program");
    ::glAttachShader(program, vertex_shader);
    ::glAttachShader(program, fragment_shader);
    ::glLinkProgram(program);

    ::GLuint vao{};
    ::glGenVertexArrays(1, &vao);
    ::GLuint vbo{};
    ::glGenBuffers(1, &vbo);
    ::glBindVertexArray(vao);
    ::glBindBuffer(GL_ARRAY_BUFFER, vbo);
    ::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    ::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    ::glEnableVertexAttribArray(1);
    ::glBindVertexArray(0);







    ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while(window.running())
    {
        ::glClear(GL_COLOR_BUFFER_BIT);
        ::glUseProgram(program);
        ::glBindVertexArray(vao);
        ::glDrawArrays(GL_TRIANGLES, 0, 3);
        window.swap();
    }
    
    return 0;
    

}