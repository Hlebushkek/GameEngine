#pragma once

#include "Core.hpp"
#include <glm/glm.hpp>

namespace Engine
{
    class ENGINE_API RayCast
    {
    public:
        RayCast();
        ~RayCast() = default;

        static glm::vec4 GetVectorForMouse();
    };
}