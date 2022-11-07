#pragma once

#include "Core.hpp"
#include "Primitive.hpp"

namespace Engine
{
    class ENGINE_API Cube : public Primitive
    {
    public:
        Cube(int excludedFaces = 0);
    };
}