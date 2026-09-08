#include "buffer.hpp"
#include "opengl.hpp"
#include "vendor/opengl/glext.h"
#include <cstddef>
#include <cstdint>
#include <gl/gl.h>
#include <span>

namespace game
{
    Buffer::Buffer(std::uint32_t size) : m_buffer{0u, [](auto buffer) { glDeleteBuffers(1, &buffer ); }}
    {
        ::glCreateBuffers(1, &m_buffer);
        ::glNamedBufferStorage(m_buffer, size, nullptr, GL_DYNAMIC_STORAGE_BIT);

    }
    void Buffer::write(std::span<const std::byte> data, std::size_t offset) const
    {
        ::glNamedBufferSubData(m_buffer, offset, data.size(), data.data());
    }
    ::GLuint Buffer::get_native_handle() const
    {
        return m_buffer;
    }

}