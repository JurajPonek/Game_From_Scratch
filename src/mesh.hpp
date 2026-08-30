#pragma once

#include "opengl.hpp"
#include "auto_release.hpp"
#include <gl/gl.h>

namespace game
{
    class Mesh
    {
        public:
            Mesh();
            void bind() const;
            void unbind() const;
        private:
            AutoRelease<::GLuint> m_vao;
            AutoRelease<::GLuint> m_vbo; 

    };
}

