#pragma once

#include "exception.hpp"
#include <format>
#include <string_view>
#include <utility>

namespace game
{
    template<typename ...Args>
    void ensure(bool predicate, std::string_view message, Args&& ...args)
    {
        if (!predicate)
            throw Exception(std::vformat(message, std::make_format_args(std::forward(args)...)));
    }


}
