#pragma once
#include <format>
namespace game
{
    class MouseEvent
    {
        public:
            MouseEvent(float delta_x, float delta_y);
            float get_delta_x() const;
            float get_delta_y() const;

        private:
            float m_delta_x;
            float m_delta_y;
    }; 

}
template<>
struct std::formatter<game::MouseEvent>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return std::cbegin(ctx);
    }
    auto format(const game::MouseEvent& event, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}\n {}", event.get_delta_x(), event.get_delta_y());
    }  
};