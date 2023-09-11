#include <iostream>
#include <SDL3/SDL.h>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_metal.h>
#include "RendererImplMetal.hpp"
#include "RenderingContext.hpp"
#include "Layer.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

namespace Engine
{

Renderer::Impl::Impl(SDL_Window* window, RenderingContext* ctx)
{
    m_metalView = SDL_Metal_CreateView(window);
    m_device = MTL::CreateSystemDefaultDevice();
    auto metalLayer = (CA::MetalLayer*)SDL_Metal_GetLayer(m_metalView);
    metalLayer->setDevice(m_device);
    ctx->device = m_device;
    m_commandQueue = m_device->newCommandQueue();
    m_renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();

    std::cout << metalLayer << std::endl;
    std::cout << metalLayer->device() << std::endl;
    std::cout << metalLayer->device()->name()->utf8String() << std::endl;

    InitDepthStencilStates();

    ImGui_ImplSDL3_InitForMetal(window);
    ImGui_ImplMetal_Init(m_device);
}

Renderer::Impl::~Impl()
{
    ImGui_ImplMetal_Shutdown();

    m_depthStencilState->release();
    m_renderPassDescriptor->release();
    m_commandQueue->release();
    m_device->release();
}

void Renderer::Impl::SetOnlyWireframeMode(bool value)
{
    
}

void Renderer::Impl::PreRenderSetup()
{
    m_pool = NS::AutoreleasePool::alloc()->init();

    RenderingContext* ctx = Renderer::GetRenderingContext();
    ctx->drawable = ((CA::MetalLayer*)SDL_Metal_GetLayer(m_metalView))->nextDrawable();

    ctx->commandBuffer = m_commandQueue->commandBuffer();

    m_renderPassDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.2, 0.2, 0.2, 1));
    m_renderPassDescriptor->colorAttachments()->object(0)->setTexture(ctx->drawable->texture());
    m_renderPassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    m_renderPassDescriptor->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);

    ctx->renderEncoder = ctx->commandBuffer->renderCommandEncoder(m_renderPassDescriptor);
    NS::String* debugGroupName = NS::String::string("ImGui Demo", NS::ASCIIStringEncoding);
    ctx->renderEncoder->pushDebugGroup(debugGroupName);

    ctx->renderEncoder->setDepthStencilState(m_depthStencilState);
}

void Renderer::Impl::PostRenderSetup()
{
    RenderingContext* ctx = Renderer::GetRenderingContext();
    ctx->renderEncoder->endEncoding();
    ctx->renderEncoder->popDebugGroup();
    ctx->commandBuffer->presentDrawable(ctx->drawable);
    ctx->commandBuffer->commit();

    m_pool->release();
}

void Renderer::Impl::RenderLayer(Layer* layer)
{

}

void Renderer::Impl::PreImGuiRenderSetup()
{
    ImGui_ImplMetal_NewFrame(m_renderPassDescriptor);
}

void Renderer::Impl::PostImGuiRenderSetup()
{
    RenderingContext* ctx = Renderer::GetRenderingContext();
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), ctx->commandBuffer, ctx->renderEncoder);
}

void Renderer::Impl::InitDepthStencilStates()
{
    MTL::DepthStencilDescriptor* depthSetncilDesc = MTL::DepthStencilDescriptor::alloc()->init();
    depthSetncilDesc->setDepthCompareFunction(MTL::CompareFunction::CompareFunctionLess);
    depthSetncilDesc->setDepthWriteEnabled(true);

    m_depthStencilState = m_device->newDepthStencilState(depthSetncilDesc);

    depthSetncilDesc->release();
}


}