#pragma once

#include "key_event.hpp"
#include "stop_event.hpp"
#include <variant>
namespace game
{
    using Event = std::variant<StopEvent, KeyEvent>;
}