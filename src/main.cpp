
#include "auto_release.hpp"
#include "mesh.hpp"
#include "src/opengl.hpp"
#include "vendor/opengl/glext.h"
#include "window.hpp"
#include "opengl.hpp"
#include <gl/gl.h>
#include <stdexcept>
#include <string_view>
#include "shader.hpp"
#include "material.hpp"

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
}

int main()
{
    game::Window window{800u, 600u};
    auto vertex_shader = game::Shader(vertex_shader_source, game::ShaderType::VERTEX);
    auto fragment_shader = game::Shader(fragment_shader_source, game::ShaderType::FRAGMENT);
    auto material = game::Material{vertex_shader, fragment_shader};
    auto mesh = game::Mesh{};






    ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while(window.running())
    {
        ::glClear(GL_COLOR_BUFFER_BIT);
        ::glUseProgram(material.get_native_handle());
        mesh.bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 3);
        mesh.unbind();
        window.swap();
    }
    
    return 0;
    

}