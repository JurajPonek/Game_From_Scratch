
#include "material.hpp"
#include "shader.hpp"

#include "error.hpp"
#include "opengl.hpp"
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
        GLint res{};
        ::glGetProgramiv(m_handle, GL_LINK_STATUS, &res);
        if (res != GL_TRUE)
        {
            char log[512];
            ::glGetProgramInfoLog(m_handle, sizeof(log), nullptr, log);

            ensure(res, "Failed to link program\n{}", log);
        }
    }
    GLuint Material::get_native_handle() const
    {
        return m_handle;
    }
}