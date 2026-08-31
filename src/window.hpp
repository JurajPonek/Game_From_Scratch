#pragma once
#include <Windows.h>
#include <winuser.h>
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
            bool running() const;
            void swap() const;


            
        private:
            AutoRelease<::HWND, nullptr> m_handle; 
            AutoRelease<::HDC> m_dc;
            WNDCLASS m_windowClass;




    };



}


