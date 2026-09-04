#pragma once

#include <vector>
#include "entity.hpp"


namespace game
{
    struct Scene
    {
        const std::vector<const Entity*> m_entities;
    };

}

