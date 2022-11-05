#pragma once

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

#include "Core.hpp"
#include "Event.hpp"
#include "IRenderable.hpp"

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
        virtual void OnEvent(SDL_Event& event) {}

        virtual void OnImGuiRender() {}

        inline const char* GetName() const { return layerName; }

        inline void AddRenderableObject(IRenderable* object) { renderableObjects.emplace_back(object); }

    private:
        const char* layerName;
        std::vector<IRenderable*> renderableObjects;
    };
}