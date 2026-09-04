
#include "mesh.hpp"
#include "opengl.hpp"
#include "auto_release.hpp"
#include "vertex_data.hpp"

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
        ::glGenVertexArrays(1, &m_vao);
        ::glGenBuffers(1, &m_vbo);
        ::glBindVertexArray(m_vao);
        ::glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
        ::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
        ::glEnableVertexAttribArray(0);
        ::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        ::glEnableVertexAttribArray(1);
        ::glBindVertexArray(0);
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
