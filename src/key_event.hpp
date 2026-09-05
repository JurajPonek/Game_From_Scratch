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
template<>
struct std::formatter<game::KeyEvent>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return std::cbegin(ctx);
    }
    auto format(const game::KeyEvent& event, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}\n {}", event.get_key(), event.get_state());
    }  
};

