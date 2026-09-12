#pragma once
#include <Windows.h>
#include <winuser.h>
#include "event.hpp"
#include <optional>
#include <cstdint>
#include "auto_release.hpp"
namespace game
{ 
    class Window
    {
        public:
            Window(std::uint32_t width, std::uint32_t height);
            ~Window() = default; 
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;
            Window(Window&&) = default;
            Window& operator=(Window&&) = default;
            std::optional<Event> pump_event() const;
            void swap() const;
            ::HWND get_native_handle() const; 
            std::uint32_t get_width() const;
            std::uint32_t get_height() const;
            
        private:
            AutoRelease<::HWND, nullptr> m_handle; 
            AutoRelease<::HDC> m_dc;
            WNDCLASS m_windowClass;
            std::uint32_t m_width;
            std::uint32_t m_height;



    };



}


