#pragma once

#include "imgui.h"
#include "mouse_button_evet.hpp"
#include <windows.h>

namespace game
{
    class DebugUI
    {
        public:
            DebugUI(HWND window);
            ~DebugUI();
            void render() const;
            void add_mouse_event(const MouseButtonEvent& event) const;

        private:
    };
}