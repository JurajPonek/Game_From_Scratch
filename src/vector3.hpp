#pragma once

#include <cmath>

namespace game 
{
    struct Vector3
    {
        float x{};
        float y{};
        float z{};

        static constexpr Vector3 normalize(const Vector3& vec)
        {
            auto length = std::hypot(vec.x, vec.y, vec.z);
            return {vec.x / length, vec.y / length, vec.z / length};
        }
        
        static constexpr Vector3 cross(const Vector3& vec1, const Vector3& vec2)
        {
            const auto i = (vec1.y * vec2.z) - (vec1.z * vec2.y);
            const auto j = -((vec1.x * vec2.z) - (vec1.z * vec2.x));
            const auto k = (vec1.x * vec2.y) - (vec1.y * vec2.x);
            return {i, j, k};
        }
    };

    constexpr Vector3& operator-=(Vector3& vec1, const Vector3& vec2)
    {
        vec1.x -= vec2.x;
        vec1.y -= vec2.y;
        vec1.z -= vec2.z;
        return vec1;
    }

    constexpr Vector3 operator-(const Vector3& vec1, const Vector3& vec2)
    {
        Vector3 res{vec1};
        return res -= vec2;
    }

    constexpr Vector3& operator+=(Vector3& vec1, const Vector3& vec2)
    {
        vec1.x += vec2.x;
        vec1.y += vec2.y;
        vec1.z += vec2.z;
        return vec1;
    }
    
    constexpr Vector3 operator+(const Vector3& vec1, const Vector3& vec2)
    {
        Vector3 res{vec1};
        return res += vec2;
    }

    constexpr Vector3 operator-(const Vector3& vec)
    {
        return {-vec.x, -vec.y, -vec.z};
    }


}