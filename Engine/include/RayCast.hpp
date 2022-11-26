#pragma once

#include "Core.hpp"

namespace Engine
{
    class ENGINE_API RayCast
    {
    public:
        RayCast();
        ~RayCast() = default;

        static bool GetObjects();
    };
}