#pragma once

#include "Layer.hpp"

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

		void Begin();
		void End();
        
        static ImGuiContext* GetImguiContext() { return imguiContext; }
        
    private:
        static ImGuiContext* imguiContext;
    
    };
}
