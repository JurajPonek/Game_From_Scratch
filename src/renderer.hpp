#pragma once

#include "mesh.hpp"
#include "material.hpp"

namespace game
{
    class Renderer
    {
        public:
            Renderer(Material material);
            void render() const;

        private:
            Mesh m_mesh;
            Material m_material;
    };
}