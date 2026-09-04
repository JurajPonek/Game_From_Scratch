#include "key_event.hpp"
#include "key.hpp"

namespace game
{
    KeyEvent::KeyEvent(Key key, KeyState state)
    : m_key(key), m_state(state)
    {

    }
    Key KeyEvent::get_key() const
    {
        return m_key;
    }
    KeyState KeyEvent::get_state() const
    {
        return m_state;
    }
}