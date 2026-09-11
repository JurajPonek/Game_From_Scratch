#include "entity.hpp"
#include "sampler.hpp"
#include "texture.hpp"
#include <vector>

namespace game
{
    Entity::Entity(const Mesh* mesh, const Material* material, const Vector3& position, const std::vector<Texture*> texture, const Sampler* sampler)
    :   m_model{position}, m_mesh(mesh), m_material(material), m_texture{texture}, m_sampler{sampler}
    {

    }

    std::span<const float> Entity::get_model_matrix() const
    {
        return m_model.data();
    }

    const Mesh* Entity::get_mesh() const
    {
        return m_mesh;
    }
    const Material* Entity::get_material() const
    {
        return m_material;
    }
    std::vector<Texture*> Entity::get_textures() const
    {
        return m_texture; 
    }
    const Sampler* Entity::get_sampler() const
    {
        return m_sampler; 
    }


}