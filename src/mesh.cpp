
#include "mesh.hpp"
#include "opengl.hpp"
#include "auto_release.hpp"
#include "vendor/opengl/glext.h"
#include "vertex_data.hpp"
#include <cstddef>
#include <gl/gl.h>

namespace 
{
    static constexpr game::VertexData vertex_data[] = 
{

    // Zadná stena
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},

    // Predná stena
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},

    // Ľavá stena
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
    
    // Pravá stena
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},

    // Spodná stena
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},

    // Vrchná stena
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}}
};
}

namespace game
{
    Mesh::Mesh() 
    : m_vao({0u, [](auto vao){::glDeleteVertexArrays(1, &vao);}}), 
      m_vbo({0u, [](auto vbo){glDeleteBuffers(1, &vbo);}})
    {
        ::glCreateBuffers(1, &m_vbo);
        ::glNamedBufferStorage(m_vbo, sizeof(vertex_data), vertex_data, GL_DYNAMIC_STORAGE_BIT); 
        ::glCreateVertexArrays(1, &m_vao);

        ::glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(VertexData));
        ::glEnableVertexArrayAttrib(m_vao, 0);
        ::glEnableVertexArrayAttrib(m_vao, 1);
        ::glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
        ::glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, color));
        ::glVertexArrayAttribBinding(m_vao, 0, 0);
        ::glVertexArrayAttribBinding(m_vao, 1, 0);
    }
    void Mesh::bind() const
    {
        ::glBindVertexArray(m_vao);
    }
    void Mesh::unbind() const
    {
        ::glBindVertexArray(0);
    }

}
