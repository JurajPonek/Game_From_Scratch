#include <chrono>
#include <ranges>
#include <unordered_map>
#include "entity.hpp"
#include "key.hpp"
#include "key_event.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "stop_event.hpp"
#include "vector3.hpp"
#include "window.hpp"
#include <concepts>
#include <print>
#include <string_view>
#include "shader.hpp"
#include "material.hpp"
#include "renderer.hpp"
#include "log.hpp"
#include <iostream>
#include "exception.hpp"
#include "camera.hpp"
#include <numbers>
#include <type_traits>
#include <variant>
#include <vector>


namespace  
{
    static constexpr auto vertex_shader_source = R"(
    #version 460 core
    
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 in_color;

    out vec3 out_color;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    
    void main()
    {
        gl_Position = projection * view * model * vec4(position, 1.0);
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
    try 
    {
        game::Window window{800u, 600u};
        const auto vertex_shader = game::Shader(vertex_shader_source, game::ShaderType::VERTEX);
        const auto fragment_shader = game::Shader(fragment_shader_source, game::ShaderType::FRAGMENT);
        auto material = game::Material{vertex_shader, fragment_shader};
        auto mesh = game::Mesh{};
        const auto renderer = game::Renderer{};
        std::vector<game::Entity> entities{};
        for (auto i {-10}; i < 10; i++)
        {
            for (auto j {-10}; j < 10; j++)
            {
                entities.emplace_back(&mesh, &material, 
                game::Vector3{static_cast<float>(i) * 2.5f, -2.0f, static_cast<float>(j) * 2.5f});
            }
        }
        
        const auto scene = game::Scene{entities | std::views::transform([](const auto& e){return &e;}) | std::ranges::to<std::vector>()};
        auto camera = game::Camera{{0.0f, 0.0f, 6.0f}, {0.0f, 1.0f, 0.0f},{0.0f, 1.0f, 0.0f}, std::numbers::pi_v<float> / 4, 800.0f, 600.0f, 0.1, 100.0f};
        auto running = true;
        auto key_states = std::unordered_map<game::Key, bool>{};
        auto last_time = std::chrono::high_resolution_clock::now();
        float speed = 20.0f;

        while(running)
        {
            auto current_time = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float>(current_time - last_time).count();
            last_time = current_time;
            auto event = window.pump_event();
            while(event && running)
            {
                std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::same_as<T, game::StopEvent>) 
                    {
                        running = false;
                    }
                    else if constexpr (std::same_as<T, game::KeyEvent>) 
                    {
                        if(arg.get_key() == game::Key::ESC)
                        {
                            running = false;
                        }
                        key_states[arg.get_key()] = arg.get_state() == game::KeyState::DOWN ? true : false;
                    }

                }

                ,*event);
                event = window.pump_event();
            }
            auto velocity = game::Vector3
            {
                (key_states[game::Key::D] ? 1.0f : 0.0f) + (key_states[game::Key::A] ?  -1.0f : 0.0f),
                0.0f,
                (key_states[game::Key::S] ? 1.0f : 0.0f) + (key_states[game::Key::W] ?  -1.0f : 0.0f),
            };
            camera.translate(game::Vector3::normalize(velocity) * speed * dt);
            renderer.render(camera, scene);
            window.swap();
            
            
        }
    


    } catch (game::Exception& err) 
    {
        std::println(std::cerr, "exception {}", err);
    } catch(...)
    {
        std::println(std::cerr, "Unknown exception");
    }




    return 0;
    }