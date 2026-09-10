#pragma once

#include "exception.hpp"
#include <format>
#include <memory>
#include <string_view>
#include <utility>

namespace game
{
    template<typename ...Args>
    void ensure(bool predicate, std::string_view message, Args&& ...args)
    {
        if (!predicate)
            throw Exception(std::vformat(message, std::make_format_args(std::forward<Args>(args)...)));
    }
    
    template<typename T, typename D, typename... Args>
    void ensure(std::unique_ptr<T, D>& obj, std::string_view message, Args&& ...args)
    {
        ensure(!!obj, message, std::forward<Args>(args)...);
    }


}
