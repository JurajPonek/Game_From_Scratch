
#include "material.hpp"
#include "shader.hpp"
#include <stdexcept>

namespace game
{

    Material::Material(const Shader& vertex_shader, const Shader& fragment_shader) : m_handle({})
    {
        if (vertex_shader.get_type() != ShaderType::VERTEX)
        {
            throw std::runtime_error("Shader is not vertex shader");
        }
        if (fragment_shader.get_type() != ShaderType::FRAGMENT)
        {
            throw std::runtime_error("Shader is not fragment shader");
        }
        m_handle = game::AutoRelease<::GLuint>
        {
            ::glCreateProgram(), ::glDeleteProgram
        };
        if (!m_handle) throw std::runtime_error("failed to create program");
        ::glAttachShader(m_handle, vertex_shader.get_native_handle());
        ::glAttachShader(m_handle, fragment_shader.get_native_handle());
        ::glLinkProgram(m_handle);
    }
    GLuint Material::get_native_handle() const
    {
        return m_handle;
    }
}