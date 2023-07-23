#include <imgui.h>
#define IMGUI_IMPL_OPENGL_ES2
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>
#include "ImGuiLayer.hpp"
#include "Application.hpp"

namespace Engine
{
    ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

    void ImGuiLayer::OnAttach()
    {

    }

    void ImGuiLayer::OnDetach()
    {
        
    }

    void ImGuiLayer::OnEvent(SDL_Event& event)
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}