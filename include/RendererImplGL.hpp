#pragma once

#include "Renderer.hpp"

namespace Engine
{

class Renderer::Impl
{
public:
    Impl(SDL_Window* window, RenderingContext* ctx);
    ~Impl();

    void SetOnlyWireframeMode(bool value);

    void PreRenderSetup();

    void RenderLayer(Layer* layer);
    void RenderObject();
    void RenderMesh();

    void PostRenderSetup();

    void PreImGuiRenderSetup();
    void PostImGuiRenderSetup();

private:
    void InitGLAD();
    void InitGLOptions();
    void InitSDLGLOptions(RenderingContext* ctx);

private:
    SDL_Window* m_window;

};

}