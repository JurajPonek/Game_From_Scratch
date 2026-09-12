#pragma once
#include <format>

namespace game
{
    enum class MouseButtonState
    {
        UP,
        DOWN
    };
    class MouseButtonEvent
    {
      public:
        MouseButtonEvent(float x,  float y, MouseButtonState state);
        float get_x() const;
        float get_y() const;
        MouseButtonState get_state() const;
      private:
        float m_x;
        float m_y;
        MouseButtonState m_state;
    };

} // namespace game
