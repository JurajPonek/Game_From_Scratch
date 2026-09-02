#pragma once

#include <vector>
#include "entity.hpp"


namespace game
{
    struct Scene
    {
        const std::vector<Entity*> m_entities;
    };

}

