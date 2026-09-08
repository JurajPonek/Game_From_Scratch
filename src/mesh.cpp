
#include "mesh.hpp"
#include "auto_release.hpp"
#include "opengl.hpp"
#include "vendor/opengl/glext.h"
#include "vertex_data.hpp"
#include <cstddef>
#include <cstdint>
#include <gl/gl.h>
#include <iterator>


namespace
{
    constexpr game::VertexData vertex_data[] = 
    {
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}}, {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}}, {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}},  {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},  {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}}
    
    };

    constexpr GLuint indices[] = 
    {
        0, 1, 5, 5, 4, 0,
        1, 2, 6, 6, 5, 1,
        2, 3, 7, 7, 6, 2,
        3, 0, 4, 4, 7, 3,
        3, 2, 1, 1, 0, 3,
        4, 5, 6, 6, 7, 4
    
    };
} // namespace

namespace game
{
    Mesh::Mesh()
        : m_vao({0u, [](auto vao) { ::glDeleteVertexArrays(1, &vao); }}),
          m_vbo({0u, [](auto vbo) { glDeleteBuffers(1, &vbo); }}), m_index_count(sizeof(indices) / sizeof(GLuint)),
          m_index_offset(sizeof(vertex_data))
    {
        ::glCreateBuffers(1, &m_vbo);
        ::glNamedBufferStorage(m_vbo, sizeof(vertex_data) + sizeof(indices), vertex_data, GL_DYNAMIC_STORAGE_BIT);
        ::glNamedBufferSubData(m_vbo, 0, sizeof(vertex_data), vertex_data);
        ::glNamedBufferSubData(m_vbo, sizeof(vertex_data), sizeof(indices), indices);

        ::glCreateVertexArrays(1, &m_vao);
        ::glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(VertexData));
        ::glVertexArrayElementBuffer(m_vao, m_vbo);

        ::glEnableVertexArrayAttrib(m_vao, 0);
        ::glEnableVertexArrayAttrib(m_vao, 1);

        ::glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
        ::glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, color));

        ::glVertexArrayAttribBinding(m_vao, 0, 0);
        ::glVertexArrayAttribBinding(m_vao, 1, 0);
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
