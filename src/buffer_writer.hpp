#pragma once

#include "buffer.hpp"
#include <cstddef>
#include <cstdint>
#include <span>
namespace game
{
    class BufferWriter
    {
      public:
        BufferWriter(const Buffer& buffer) : m_buffer{buffer}, m_offset{} {}
      template <typename T, std::size_t N>
      void write(const T(&data)[N])
      {
        const auto size = sizeof(T) * N;
        m_buffer.write({reinterpret_cast<const std::byte*>(data), size}, m_offset);
        m_offset += size;
      }
      template<typename T>
      void write(std::span<const T> data)
      {
          m_buffer.write(std::as_bytes(data), m_offset);
          m_offset += data.size_bytes();
      }

      private : 
        const Buffer& m_buffer;
        std::size_t m_offset;
    };

} // namespace game