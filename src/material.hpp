#pragma once
#include "opengl.hpp"
#include "auto_release.hpp"
#include "shader.hpp"
#include <gl/gl.h>

namespace game
{
    class Material
    {
        public:
            Material(const Shader& vertex_shader, const Shader& fragment_shader);
            GLuint get_native_handle() const;
        private:
            AutoRelease<GLuint> m_handle;


    };
}