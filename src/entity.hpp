#pragma once

#include "material.hpp"
#include "matrix4.hpp"
#include "mesh.hpp"
#include "sampler.hpp"
#include "texture.hpp"
#include "vector3.hpp"
#include <span>


namespace game
{
    class Entity
    {
      public:
        Entity(const Mesh* mesh, const Material* material, const Vector3& position, const Texture* texture, const Sampler* sampler);

        std::span<const float> get_model_matrix() const;
        const Mesh* get_mesh() const;
        const Material* get_material() const;
        const Texture* get_texture() const;
        const Sampler* get_sampler() const;
      private:
        Matrix4 m_model;
        const Mesh* m_mesh;
        const Material* m_material;
        const Texture* m_texture;
        const Sampler* m_sampler;
    };

} // namespace game