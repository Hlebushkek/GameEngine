#include "BoxCollider.hpp"

namespace Engine
{
    BoxCollider::BoxCollider(glm::vec3 size, glm::vec3 rotation, glm::vec3 scale, glm::vec3 positionOffset)
    {
        this->size = size;
        this->rotation = rotation;
        this->scale = scale;
        this->positionOffset = positionOffset;
    }
}
