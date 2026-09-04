#include "camera.hpp"
#include "matrix4.hpp"

namespace game
{
    Camera::Camera(const Vector3& position, const Vector3& look_at, const Vector3& up,
                    float fov, float width, float height, float near_plane, float far_plane)
        : m_view{Matrix4::look_at(position, look_at, up)},
          m_projection{Matrix4::perspective(fov, width, height, near_plane, far_plane), 
        }, m_position{position},
            m_direction{look_at},
            m_up(up)

    {
        
    }

    std::span<const float, 16> Camera::get_view() const
    {
        return m_view.data();
    }
    std::span<const float, 16> Camera::get_projection() const
    {
        return m_projection.data();
    }

    void Camera::translate(const Vector3& translation)
    {
        m_position += translation;
        m_direction += translation;
        m_view = Matrix4::look_at(m_position, m_direction, m_up); 
    }


}
