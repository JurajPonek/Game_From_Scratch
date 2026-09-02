#pragma once

#include "mesh.hpp"
#include "material.hpp"
#include "matrix4.hpp"
#include "vector3.hpp"
#include <span>

namespace game
{
    class Entity
    {
        public:
            Entity(const Mesh* mesh, const Material* material, const Vector3& postion);

            std::span<const float> get_model_matrix() const;
            const Mesh* get_mesh() const;
            const Material* get_material() const;

        private:
            Matrix4 m_model;
            const Mesh* m_mesh;
            const Material* m_material;

    };

}