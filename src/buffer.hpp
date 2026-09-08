#pragma once

#include "auto_release.hpp"
#include "opengl.hpp"
#include <cstddef>
#include <cstdint>
#include <gl/gl.h>
#include <span>

namespace game
{
    class Buffer
    {
        public:
            Buffer(std::uint32_t size);
            void write(std::span<const std::byte> data, std::size_t offset) const;
            ::GLuint get_native_handle() const;
        private:
            AutoRelease<GLuint> m_buffer;
    };
} // namespace game