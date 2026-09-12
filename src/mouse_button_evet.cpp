#include "mouse_button_evet.hpp"
namespace game
{


    MouseButtonEvent::MouseButtonEvent(float x, float y, MouseButtonState state) : m_x{x}, m_y{y}, m_state{state} {}
    float MouseButtonEvent::get_x() const { return m_x; }
    float MouseButtonEvent::get_y() const { return m_y; }
    MouseButtonState MouseButtonEvent::get_state() const { return m_state; }
} // namespace game