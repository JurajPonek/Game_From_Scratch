
#include "material.hpp"
#include "shader.hpp"
#include <stdexcept>
#include "error.hpp"

namespace game
{

    Material::Material(const Shader& vertex_shader, const Shader& fragment_shader) : m_handle({})
    {
        ensure(vertex_shader.get_type() == ShaderType::VERTEX,  "Shader is not vertex shader");
        ensure(fragment_shader.get_type() == ShaderType::FRAGMENT, "Shader is not fragment shader");

        m_handle = game::AutoRelease<::GLuint>
        {
            ::glCreateProgram(), ::glDeleteProgram
        };
        ensure(m_handle, "failed to create program");
        ::glAttachShader(m_handle, vertex_shader.get_native_handle());
        ::glAttachShader(m_handle, fragment_shader.get_native_handle());
        ::glLinkProgram(m_handle);
    }
    GLuint Material::get_native_handle() const
    {
        return m_handle;
    }
}