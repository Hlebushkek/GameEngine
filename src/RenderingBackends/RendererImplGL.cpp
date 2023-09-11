#define IMGUI_IMPL_OPENGL_ES2
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "Renderer.hpp"
#include "RendererImplGL.hpp"
#include "RenderingContext.hpp"
#include "Layer.hpp"

namespace Engine
{

Renderer::Impl::Impl(SDL_Window* window, RenderingContext* ctx)
    : m_window(window)
{
    InitSDLGLOptions(ctx);
    InitGLAD();
    InitGLOptions();

    ImGui_ImplSDL3_InitForOpenGL(window, ctx->glContext);
    ImGui_ImplOpenGL3_Init("#version 410");
}

Renderer::Impl::~Impl()
{
    ImGui_ImplSDL3_Shutdown();
}

void Renderer::Impl::InitGLAD()
{
    int status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    assert(status);
}

void Renderer::Impl::InitGLOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::Impl::InitSDLGLOptions(RenderingContext* ctx)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    ctx->glContext = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, ctx->glContext);
}

void Renderer::Impl::SetOnlyWireframeMode(bool value)
{
    glPolygonMode(GL_FRONT_AND_BACK, value ? GL_LINE : GL_FILL);
}

void Renderer::Impl::PreRenderSetup()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Impl::RenderLayer(Layer* layer)
{

}

void Renderer::Impl::PostRenderSetup()
{
    glFlush();

    SDL_GL_SwapWindow(m_window);

    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Impl::PreImGuiRenderSetup()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void Renderer::Impl::PostImGuiRenderSetup()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}