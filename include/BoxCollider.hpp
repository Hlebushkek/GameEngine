#pragma once

#include <glm/glm.hpp>
#include "Collider.hpp"

namespace Engine
{
    class ENGINE_API BoxCollider : public Collider
    {
    public:
        BoxCollider(glm::vec3 size, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1),
            glm::vec3 positionOffset = glm::vec3(0));
        virtual ~BoxCollider() = default;

        virtual std::optional<glm::vec3> CollidesWith(const Ray& ray, const Transform& transform) override;

    private:
        glm::vec3 size;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::vec3 positionOffset;

    };
}