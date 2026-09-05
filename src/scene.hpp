#pragma once

#include "entity.hpp"
#include <vector>



namespace game
{
    struct Scene
    {
        const std::vector<const Entity*> m_entities;
    };

} // namespace game
