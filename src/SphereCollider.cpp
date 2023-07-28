#include <glm/glm.hpp>
#include "SphereCollider.hpp"

namespace Engine
{

SphereCollider::SphereCollider(float radius, glm::vec3 positionOffset)
    : radius(radius), positionOffset(positionOffset) {}

bool SphereCollider::CollidesWith(const Ray &ray, const Transform& transform)
{
    glm::vec3 oc = ray.origin - transform.GetPosition();
    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2.0f * glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}

}