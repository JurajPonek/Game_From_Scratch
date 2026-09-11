#pragma once

#include "buffer.hpp"
#include "camera.hpp"
#include "scene.hpp"

namespace game
{
    class Renderer
    {
        public:
            Renderer();
            void render(const Camera& camera, const Scene& scene) const;
        private:
            Buffer m_camera_buffer;
            Buffer m_light_buffer; 
    };
}