#include <glm/glm.hpp>
#include "SphereCollider.hpp"
#include "Sphere.hpp"

namespace Engine
{

SphereCollider::SphereCollider(float radius, glm::vec3 positionOffset)
    : radius(radius), positionOffset(positionOffset) {}

std::optional<glm::vec3> SphereCollider::CollidesWith(const Ray &ray, std::shared_ptr<Transform> transform)
{
    glm::vec3 oc = ray.origin - transform->GetPosition() - positionOffset;
    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2.0f * glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - radius * radius * transform->GetScale().x * transform->GetScale().x;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return std::nullopt;

    float t = (-b - glm::sqrt(discriminant)) / (2.0f * a);
    return ray.origin + ray.direction() * t;
}

}