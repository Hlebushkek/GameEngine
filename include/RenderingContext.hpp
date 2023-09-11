#pragma once

#ifdef ENABLE_METAL
namespace MTL { class Device; class RenderCommandEncoder; class CommandBuffer; }
namespace CA { class MetalDrawable; }
#else
#endif

struct ImGuiContext;

namespace Engine
{

struct RenderingContext
{
#ifdef ENABLE_METAL
    MTL::Device* device;
    MTL::RenderCommandEncoder* renderEncoder;
    MTL::CommandBuffer* commandBuffer;
    CA::MetalDrawable* drawable;
#else
    void* glContext;
#endif
    ImGuiContext* imguiContext;
};

}