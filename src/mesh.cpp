
#include "mesh.hpp"
#include "auto_release.hpp"
#include "buffer_writer.hpp"
#include "opengl.hpp"
#include "vendor/opengl/glext.h"
#include "vertex_data.hpp"
#include <cstddef>
#include <cstdint>
#include <gl/gl.h>
#include <iterator>


namespace
{
    constexpr game::VertexData vertex_data[] = {
        // Predná stena (+Z) -> normála {0.0f, 0.0f, 1.0f}
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 0
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  // 1
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // 2
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},  // 3

        // Zadná stena (-Z) -> normála {0.0f, 0.0f, -1.0f}
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},  // 4
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // 5
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  // 6
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},   // 7

        // Pravá stena (+X) -> normála {1.0f, 0.0f, 0.0f}
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},  // 8
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 9
        {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},  // 10
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},   // 11

        // Ľavá stena (-X) -> normála {-1.0f, 0.0f, 0.0f}
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 12
        {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // 13
        {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},   // 14
        {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // 15

        // Horná stena (+Y) -> normála {0.0f, 1.0f, 0.0f}
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},  // 16
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // 17
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},  // 18
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // 19

        // Spodná stena (-Y) -> normála {0.0f, -1.0f, 0.0f}
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}, // 20
        {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},  // 21
        {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},   // 22
        {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}   // 23
    };

    constexpr GLuint indices[] = {
        0,  1,  2,  2,  3,  0,  // Predná
        4,  5,  6,  6,  7,  4,  // Zadná
        8,  9,  10, 10, 11, 8,  // Pravá
        12, 13, 14, 14, 15, 12, // Ľavá
        16, 17, 18, 18, 19, 16, // Horná
        20, 21, 22, 22, 23, 20  // Spodná
    };  
} // namespace

namespace game
{
    Mesh::Mesh()
        : m_vao({0u, [](auto vao) { ::glDeleteVertexArrays(1, &vao); }}),
          m_vbo{sizeof(vertex_data) + sizeof(indices)}, m_index_count(sizeof(indices) / sizeof(GLuint)),
          m_index_offset(sizeof(vertex_data))
    {
        {
            BufferWriter writer{m_vbo};
            writer.write(vertex_data);
            writer.write(indices);
        }

        ::glCreateVertexArrays(1, &m_vao);
        ::glVertexArrayVertexBuffer(m_vao, 0, m_vbo.get_native_handle(), 0, sizeof(VertexData));
        ::glVertexArrayElementBuffer(m_vao, m_vbo.get_native_handle());

        ::glEnableVertexArrayAttrib(m_vao, 0);
        ::glEnableVertexArrayAttrib(m_vao, 1);
        ::glEnableVertexArrayAttrib(m_vao, 2);

        ::glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
        ::glVertexArrayAttribFormat(m_vao,  1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, normal));
        ::glVertexArrayAttribFormat(m_vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(VertexData, uv));

        ::glVertexArrayAttribBinding(m_vao, 0, 0);
        ::glVertexArrayAttribBinding(m_vao, 1, 0);
        ::glVertexArrayAttribBinding(m_vao, 2, 0);
    }
    void Mesh::bind() const { ::glBindVertexArray(m_vao); }
    void Mesh::unbind() const { ::glBindVertexArray(0); }
    std::uint32_t Mesh::get_index_count() const
    {
        return m_index_count;
    }
    std::uintptr_t Mesh::get_index_offset() const
    {
        return m_index_offset;
    }

} // namespace game
