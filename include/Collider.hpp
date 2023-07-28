#pragma once

#include "Core.hpp"
#include "Ray.hpp"
#include "Transform.hpp"

namespace Engine
{

class ENGINE_API Collider
{
public:
    virtual bool CollidesWith(const Ray& ray, const Transform& transform) = 0;
};

}