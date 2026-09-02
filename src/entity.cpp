#include "entity.hpp"

namespace game
{
    Entity::Entity(const Mesh* mesh, const Material* material, const Vector3& position)
    :   m_model{position}, m_mesh(mesh), m_material(material)
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

}