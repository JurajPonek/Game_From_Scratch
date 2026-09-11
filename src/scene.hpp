#pragma once

#include "entity.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include <vector>



namespace game
{
    struct DirectionalLight
    {
        Vector3 direction;
        Color color;
    };
    struct PointLight
    {
        Vector3 position;
        Color color;
    };
    struct Scene
    {
        const std::vector<const Entity*> m_entities;
        Color ambient;
        DirectionalLight directional;
        PointLight point;
    };

} // namespace game
