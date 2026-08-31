#pragma once

#include <format>
#include <iterator>
#include <stacktrace>
#include <stdexcept>
#include <string>

namespace game
{
    class Exception : public std::runtime_error
    {
        public:
            Exception(const std::string& what);
            std::string stacktrace() const;
        private:
            std::stacktrace m_trace;
    };

}

template<>
struct std::formatter<game::Exception>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return std::cbegin(ctx);
    }
    auto format(const game::Exception& ex, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}\n {}", ex.what(), ex.stacktrace());
    }  
};

