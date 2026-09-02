#pragma once

#include "camera.hpp"
#include "mesh.hpp"
#include "material.hpp"

namespace game
{
    class Renderer
    {
        public:
            Renderer(Material material);
            void render(const Camera& camera) const;

        private:
            Mesh m_mesh;
            Material m_material;
    };
}