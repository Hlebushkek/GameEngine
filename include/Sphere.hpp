#pragma once

#include "Core.hpp"
#include "Primitive.hpp"

namespace Engine
{
    class ENGINE_API Sphere : public Primitive
    {
    public:
        Sphere(float radius = 0.5f, int rings = 32, int sectors = 32);
    };
}