#pragma once

#include "key.hpp"
namespace game
{
    class KeyEvent
    {
        public:
            KeyEvent(Key key, KeyState state);
            Key get_key() const;    
            KeyState  get_state() const;

        private:
            Key m_key;
            KeyState m_state;    
    }; 

};