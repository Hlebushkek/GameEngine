#pragma once

#include "Layer.hpp"

namespace MTL { class CommandBuffer; class RenderCommandEncoder; class RenderPassDescriptor; }

namespace Engine
{
    class ENGINE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(SDL_Event& event) override;
    
    };
}
