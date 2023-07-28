#include "BoxCollider.hpp"

namespace Engine
{

BoxCollider::BoxCollider(glm::vec3 size, glm::vec3 rotation, glm::vec3 scale, glm::vec3 positionOffset)
    : size(size), rotation(rotation), scale(scale), positionOffset(positionOffset) {}

bool BoxCollider::CollidesWith(const Ray &ray, const Transform& transform)
{
    return false;
}

}
