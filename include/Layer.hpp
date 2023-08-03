#pragma once

#include <vector>
#include <iostream>
#include <SDL3/SDL.h>

#include "Core.hpp"
#include "Event.hpp"
#include "GameObject.hpp"
#include "UIObject.hpp"

namespace Engine
{
    class ENGINE_API Layer
    {
    public:
        Layer(const char* name);
        virtual ~Layer();

        std::optional<Intersection> CheckRayCast(const Ray& ray, const std::vector<int>& buttons);

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void Update() { for (auto& object : renderableObjects) object->Update(); }
        virtual void CheckCollisions();

        virtual void Render(Shader* shader);
        virtual void RenderUI(Shader* shader);
        virtual void OnImGuiRender() {}

        virtual void OnEvent(SDL_Event& event) {}

        inline const char* GetName() const { return layerName; }

        inline void AddRenderableObject(GameObject* object) { renderableObjects.emplace_back(object); }
        inline void AddUIObject(UIObject* object) { uiObjects.emplace_back(object); }

    private:
        const char* layerName;
        std::vector<GameObject*> renderableObjects;
        std::vector<UIObject*> uiObjects;
    };
}