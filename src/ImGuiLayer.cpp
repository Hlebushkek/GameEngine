#include <imgui.h>
#define IMGUI_IMPL_OPENGL_ES2
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>
#include "ImGuiLayer.hpp"
#include "Application.hpp"

namespace Engine
{
    ImGuiContext *ImGuiLayer::imguiContext = nullptr;

    ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        imguiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        
        auto app = Application::Get();
        ImGui_ImplSDL3_InitForOpenGL(app->GetWindow(), app->GetGLContext());
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext(imguiContext);
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