#pragma once

#include <optional>
#include "Core.hpp"
#include "Ray.hpp"
#include "Transform.hpp"

namespace Engine
{

class ENGINE_API Collider
{
public:
    virtual std::optional<glm::vec3> CollidesWith(const Ray& ray, const Transform& transform) = 0;
};

}