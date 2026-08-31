

#include "mesh.hpp"
#include "window.hpp"
#include <string_view>
#include "shader.hpp"
#include "material.hpp"
#include "renderer.hpp"
#include "log.hpp"

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
    const auto vertex_shader = game::Shader(vertex_shader_source, game::ShaderType::VERTEX);
    const auto fragment_shader = game::Shader(fragment_shader_source, game::ShaderType::FRAGMENT);
    auto material = game::Material{vertex_shader, fragment_shader};
    const auto renderer = game::Renderer{std::move(material)};
    auto mesh = game::Mesh{};
    game::log::debug("my arg: {}, {}", 1, "Test");
    game::log::error("my arg: {}", 1);
    game::log::warn("my arg: {}", 1);
    game::log::info("my arg: {}", 1);

    while(window.running())
    {
        renderer.render();
        window.swap();
    }
    
    return 0;
    

}