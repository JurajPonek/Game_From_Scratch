#include "debug_ui.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include "mouse_button_evet.hpp"
#include <memory>

namespace game
{
    DebugUI::DebugUI(HWND window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();
        ::ImGui_ImplWin32_InitForOpenGL(window);
        ::ImGui_ImplOpenGL3_Init();

    }
    DebugUI::~DebugUI()
    {
        ::ImGui_ImplOpenGL3_Shutdown();
        ::ImGui_ImplWin32_Shutdown();
        ::ImGui::DestroyContext();   
    }
    void DebugUI::render() const
    {
        ::ImGui_ImplOpenGL3_NewFrame();
        ::ImGui_ImplWin32_NewFrame();
        ::ImGui::NewFrame();
        bool show_demo = true;
        ::ImGui::ShowDemoWindow(&show_demo); 
        ::ImGui::Render();
        ::ImGui_ImplOpenGL3_RenderDrawData(::ImGui::GetDrawData());

    }

    void DebugUI::add_mouse_event(const MouseButtonEvent& event) const
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(0, event.get_state() == MouseButtonState::DOWN);
        
    }

}

