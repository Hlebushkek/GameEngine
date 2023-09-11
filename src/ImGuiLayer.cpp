#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include "ImGuiLayer.hpp"
#include "Application.hpp"

namespace Engine
{

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

void ImGuiLayer::OnAttach() {}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnEvent(SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

}
