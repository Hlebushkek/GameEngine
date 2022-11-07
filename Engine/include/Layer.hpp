#pragma once

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

#include "Core.hpp"
#include "Event.hpp"
#include "UIObject.hpp"

namespace Engine
{
    class ENGINE_API Layer
    {
    public:
        Layer(const char* name);
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void Update() {}

        virtual void Render(Shader* shader);
        virtual void RenderUI(Shader* shader);
        virtual void OnImGuiRender() {}

        virtual void OnEvent(SDL_Event& event) {}

        inline const char* GetName() const { return layerName; }

        inline void AddRenderableObject(IRenderable* object) { renderableObjects.emplace_back(object); }
        inline void AddUIObject(UIObject* object) { uiObjects.emplace_back(object); }

    private:
        const char* layerName;
        std::vector<IRenderable*> renderableObjects;
        std::vector<UIObject*> uiObjects;
    };
}