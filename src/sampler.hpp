#pragma once

#include "opengl.hpp"
#include "auto_release.hpp"
namespace game
{
    class Sampler
    {
      public:
        Sampler();
        ::GLuint get_native_handle() const; 
      private:
        AutoRelease<::GLuint> m_handle;
    };
} // namespace Sampler