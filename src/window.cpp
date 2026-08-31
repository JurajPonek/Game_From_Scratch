#include "window.hpp"
#include "auto_release.hpp"
#include <gl/gl.h>
#include <libloaderapi.h>
#include <minwindef.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <stdexcept>
#include <print>
#include "opengl.hpp"
#include "vendor/opengl/glext.h"
#include "vendor/opengl/wglext.h"
#define NOMINMAX



namespace 
{
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB{};
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB{};
    bool gameRunning = true;

    void APIENTRY opengl_debug_callback(GLenum source,
        [[maybe_unused]] GLenum type,
        [[maybe_unused]] GLuint id,
        [[maybe_unused]] GLenum severity, 
        [[maybe_unused]] GLsizei length,
        [[maybe_unused]] const GLchar *message,
        [[maybe_unused]] const void *userParam)
    {
        std::println("{} {} {} {} {} {}", source, type, id, severity, length, message);
    }


    LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg) 
        {
            case WM_CLOSE : gameRunning = false; break;
            case WM_KEYDOWN : std::println("Key down"); break;
        }
        return ::DefWindowProcA(hwnd, msg, wparam
            , lparam);
    }

    template<typename T>
    void resolve_gl_function(T& function, const std::string& name)
    {
        const auto address = ::wglGetProcAddress(name.c_str());
        if (!address) throw std::runtime_error("could not resolve function address");
        function = reinterpret_cast<T>(address);
        
    }
    
    void resolve_wgl_functions(HINSTANCE instance)
    {
        ::WNDCLASS wc = ::WNDCLASS
        {
            .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .lpfnWndProc = ::DefWindowProcA,
            .hInstance = instance,
            .lpszClassName = "dummy window",
        };
        if (::RegisterClassA(&wc) == 0 )
        {
            throw std::runtime_error("failed create dummy window");
        }
        auto dummy_window = game::AutoRelease<::HWND>
        {
            ::CreateWindowExA(
                0,
                wc.lpszClassName,
                wc.lpszClassName,
                CW_USEDEFAULT, 
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                nullptr,
                wc.hInstance,
                0
                ),
            ::DestroyWindow
        

        };
        auto dc = game::AutoRelease<::HDC>{::GetDC(dummy_window), [&dummy_window](auto dc) {::ReleaseDC(dummy_window, dc);}};
        if (!dc)
            throw std::runtime_error("Could not get dummy dc"); 
        auto pfd = ::PIXELFORMATDESCRIPTOR
        {
            .nSize = sizeof(::PIXELFORMATDESCRIPTOR),
            .nVersion = 1,
            .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType = PFD_TYPE_RGBA,
            .cColorBits = 32,
            .cAlphaBits = 8,
            .cDepthBits = 24,
            .cStencilBits = 8,
            .iLayerType = PFD_MAIN_PLANE, 
        };
        auto pixel_format = ::ChoosePixelFormat(dc, &pfd);
        if (pixel_format == 0)
            throw std::runtime_error("Failed to choose pixel format");
        if (::SetPixelFormat(dc, pixel_format, &pfd) == FALSE)
        {
            throw  std::runtime_error("Failed to set pixel format");
        }
        const auto context = game::AutoRelease<::HGLRC>{::wglCreateContext(dc), ::wglDeleteContext};
        if (!context) throw std::runtime_error("Failed to create wgl context");
        if (::wglMakeCurrent(dc, context) == FALSE) throw std::runtime_error("Failed to make current context");

        resolve_gl_function(wglCreateContextAttribsARB, "wglCreateContextAttribsARB");
        resolve_gl_function(wglChoosePixelFormatARB, "wglChoosePixelFormatARB");



        if (::wglMakeCurrent(dc, 0) == FALSE) throw std::runtime_error("Failed to unbind current context");

        

        
    }

    void init_opengl(HDC dc)
    {
        int pixel_format_attribs[]
        {
            WGL_DRAW_TO_WINDOW_ARB,
            GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, 
            GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,
            GL_TRUE,
            WGL_ACCELERATION_ARB,
            WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB,
            WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,
            32,
            WGL_DEPTH_BITS_ARB,
            24,
            WGL_STENCIL_BITS_ARB,
            8,
            0
        };
        auto pixel_format = 0;
        auto num_formats = UINT{};
        ::wglChoosePixelFormatARB(dc, pixel_format_attribs, 0,1,&pixel_format, &num_formats);
        if (num_formats == 0u) throw std::runtime_error("Could not choose pixel format");
        auto pfd = ::PIXELFORMATDESCRIPTOR{};
        if (::DescribePixelFormat(dc, pixel_format, sizeof(pfd), &pfd) == 0) throw std::runtime_error("failed to describe pixel format");
        if (::SetPixelFormat(dc, pixel_format, &pfd) == FALSE) throw std::runtime_error("fialed to set pixel format");
        int gl_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
};

        auto context = ::wglCreateContextAttribsARB(dc, nullptr, gl_attribs);
        if (!context) throw std::runtime_error("failed to create wgl context");

        if(::wglMakeCurrent(dc, context) == FALSE) throw std::runtime_error ("failed to make current context");


    }
    void resolve_global_opengl_functions()
    {
        #define RESOLVE(TYPE, NAME) resolve_gl_function(NAME, #NAME);
        FOR_OPENGL_FUNCTIONS(RESOLVE);
    }

    void setup_opengl_debug()
    {
        ::glEnable(GL_DEBUG_OUTPUT);
        ::glDebugMessageCallback(opengl_debug_callback, nullptr);

    }
};



namespace game
{ 
    Window::Window(std::uint32_t width, std::uint32_t height) 
    : m_handle(),m_dc({}), m_windowClass({})
    {
        
        m_windowClass = {
            .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .lpfnWndProc = window_proc,
            .hInstance = ::GetModuleHandleA(nullptr),
            .lpszClassName = "window class"
            
        };

        

        if (::RegisterClassA(&m_windowClass) == 0 )
        {
            throw std::runtime_error("failed to register class");
        }


        ::RECT rect{
            .left = {},
            .top = {},
            .right = static_cast<int>(width),
            .bottom = static_cast<int>(height)
        };
        if (::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false) == 0)
        {
            throw std::runtime_error("Could not resize window");
        }
        m_handle = { ::CreateWindowExA(
                0,
                m_windowClass.lpszClassName,
                "Window",
                WS_OVERLAPPEDWINDOW, 
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                rect.right - rect.left,
                rect.bottom - rect.top,
                nullptr,
                nullptr,
                m_windowClass.hInstance,
                nullptr
                ),
            ::DestroyWindow
        };
        m_dc = game::AutoRelease<::HDC>{::GetDC(m_handle), [this](auto dc) {::ReleaseDC(m_handle, dc);}};

        ::ShowWindow(m_handle, SW_SHOW);
        ::UpdateWindow(m_handle);

        resolve_wgl_functions(m_windowClass.hInstance);
        init_opengl(m_dc);
        resolve_global_opengl_functions();
        setup_opengl_debug();
        


    }

    bool Window::running() const
    {
        ::MSG message{};
        while(::PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE) != 0   )
        {
            ::TranslateMessage(&message);
            ::DispatchMessageA(&message);
        }
        return gameRunning;
    }

    void Window::swap() const
    {
        ::SwapBuffers(m_dc); 
    }


            

            




    };