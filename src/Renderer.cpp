#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#ifdef ENABLE_METAL
#include "RendererImplMetal.hpp"
#else
#include "RendererImplGL.hpp"
#endif
#include "Renderer.hpp"
#include "RenderingContext.hpp"
#include "Shader.hpp"
#include "Layer.hpp"

namespace Engine
{

RenderingContext* Renderer::m_renderingContext = nullptr;

Renderer::Renderer(SDL_Window* window)
{
    IMGUI_CHECKVERSION();
    m_renderingContext = new RenderingContext();

    m_renderingContext->imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    impl = std::make_unique<Impl>(window, m_renderingContext);
}

Renderer::~Renderer()
{
    if (m_renderingContext)
        delete m_renderingContext;
}

void Renderer::UseShader(Shader* shader)
{
    // impl->UseShader(shader);
}

void Renderer::SetOnlyWireframeMode(bool value)
{
    impl->SetOnlyWireframeMode(value);
}

void Renderer::PreRenderSetup()
{
    impl->PreRenderSetup();
}

void Renderer::RenderLayer(Layer *layer)
{
    impl->RenderLayer(layer);
}

void Renderer::PostRenderSetup()
{
    impl->PostRenderSetup();
}

void Renderer::PreImGuiRenderSetup()
{
    impl->PreImGuiRenderSetup();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Renderer::PostImGuiRenderSetup()
{
    ImGui::Render();
    impl->PostImGuiRenderSetup();
}

}