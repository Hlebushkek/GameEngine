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

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void Update() { for (auto& object : renderableObjects) object->Update(); }
        virtual std::optional<Intersection> CheckCollisions(const Ray& ray)
        {
            for (auto& object : renderableObjects)
            {
                auto result = object->CollidesWith(ray);
                if (result.has_value())
                    return result;
            }

            return std::nullopt;
        }

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