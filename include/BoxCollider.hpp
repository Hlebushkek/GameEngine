#pragma once

#include <glm/glm.hpp>
#include "Collider.hpp"

namespace Engine
{
    class ENGINE_API BoxCollider : public Collider
    {
    public:
        BoxCollider(glm::vec3 positionOffset = glm::vec3(0));
        virtual ~BoxCollider() = default;

        virtual std::optional<glm::vec3> CollidesWith(const Ray& ray, std::shared_ptr<Transform> transform) override;

    private:
        glm::vec3 positionOffset;

    };
}