#pragma once

#include <glm/glm.hpp>
#include "Collider.hpp"

namespace Engine
{
    class ENGINE_API SphereCollider : public Collider
    {
    public:
        SphereCollider(float radius, glm::vec3 positionOffset = glm::vec3(0));
        virtual ~SphereCollider() = default;

        virtual std::optional<glm::vec3> CollidesWith(const Ray& ray, const Transform& transform) override;
        
    private:
        float radius;
        glm::vec3 positionOffset;

    };
}