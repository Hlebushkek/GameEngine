#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Core.hpp"
#include "Event.hpp"

namespace Engine
{
    class ENGINE_API Layer
    {
    public:
        Layer(const char* name);
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void Update();
        virtual void OnEvent(Event& event);

        inline const char* GetName() const { return layerName; }

    private:
        const char* layerName;
        
    };
}