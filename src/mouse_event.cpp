
#include "mouse_event.hpp"

namespace game
{
    MouseEvent::MouseEvent(float delta_x, float delta_y)
        : m_delta_x(delta_x), m_delta_y(delta_y)
    {

    }
    float MouseEvent::get_delta_x() const
    {
        return m_delta_x;
    }
    float MouseEvent::get_delta_y() const
    {
        return m_delta_y;
    }
}



