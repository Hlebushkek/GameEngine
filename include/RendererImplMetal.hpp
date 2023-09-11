#pragma once

#include "Renderer.hpp"

namespace MTL { class Device; class RenderPassDescriptor; class CommandQueue; class DepthStencilState; }
namespace NS { class AutoreleasePool; }

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
    void PostRenderSetup();

    void PreImGuiRenderSetup();
    void PostImGuiRenderSetup();

private:
    void InitDepthStencilStates();

private:
    void* m_metalView;
    MTL::Device* m_device;
    MTL::RenderPassDescriptor* m_renderPassDescriptor;
    MTL::CommandQueue* m_commandQueue;
    MTL::DepthStencilState* m_depthStencilState;

    //Render cycle
    NS::AutoreleasePool* m_pool;

};

}