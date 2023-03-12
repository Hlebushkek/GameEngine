#include <imgui.h>
#define IMGUI_IMPL_OPENGL_ES2
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>
#include "../include/ImGuiLayer.hpp"
#include "../include/Application.hpp"

namespace Engine
{
    ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

    void ImGuiLayer::OnAttach()
    {
        std::string glsl_version = "";
        glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        Application* app = Application::Get();
        
        IMGUI_CHECKVERSION();
        app->imguiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        
        ImGui_ImplSDL3_InitForOpenGL(app->GetWindow(), app->glContext);
        ImGui_ImplOpenGL3_Init(glsl_version.c_str());
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext(Application::Get()->imguiContext);
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
        // ImGuiIO& io = ImGui::GetIO();
		// Application* app = Application::Get();
		// io.DisplaySize = ImVec2((float)app->GetWidth(), (float)app->GetHeight());

		// // Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		// // {
		// // 	SDL_GLContext* backup_current_context = Application::Get()->GetGLContext();
		// // 	ImGui::UpdatePlatformWindows();
		// // 	ImGui::RenderPlatformWindowsDefault();
		// // }
    }

}