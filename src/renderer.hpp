#pragma once

#include "camera.hpp"
#include "scene.hpp"

namespace game
{
    class Renderer
    {
        public:
            void render(const Camera& camera, const Scene& entity) const;
    };
}