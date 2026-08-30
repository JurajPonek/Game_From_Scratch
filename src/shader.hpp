#pragma once
#include <string_view>
#include "auto_release.hpp"
#include "opengl.hpp"

namespace game
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class Shader
    {
        public:
            Shader(std::string_view source, ShaderType type);
            ShaderType get_type() const;
            ::GLuint get_native_handle() const;

        private:
            AutoRelease<::GLuint> m_handle;
            ShaderType m_type;

    };
}