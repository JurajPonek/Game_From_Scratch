#pragma once

#include "vector3.hpp"
#include "color.hpp"

namespace game
{
    struct UV
    {
        float u{};
        float v{};
    };
    struct VertexData
    {
        Vector3 position{};
        Vector3 normal;
        UV uv;
    };

}

