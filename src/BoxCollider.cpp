#include <glm/gtx/norm.hpp>
#include "BoxCollider.hpp"

namespace Engine
{

BoxCollider::BoxCollider(glm::vec3 positionOffset) : positionOffset(positionOffset) {}

std::optional<glm::vec3> BoxCollider::CollidesWith(const Ray &ray, std::shared_ptr<Transform> transform)
{
    glm::vec3 center = transform->GetPosition() + positionOffset;
    glm::vec3 minBound = center - transform->GetScale() * 0.5f;
    glm::vec3 maxBound = center + transform->GetScale() * 0.5f;

    float t1 = (minBound.x - ray.origin.x) / ray.direction().x;
    float t2 = (maxBound.x - ray.origin.x) / ray.direction().x;
    float t3 = (minBound.y - ray.origin.y) / ray.direction().y;
    float t4 = (maxBound.y - ray.origin.y) / ray.direction().y;
    float t5 = (minBound.z - ray.origin.z) / ray.direction().z;
    float t6 = (maxBound.z - ray.origin.z) / ray.direction().z;

    float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
    float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

    if (tmax < 0 || tmin > tmax)
        return std::nullopt;

    float tResult = (tmin < 0) ? tmax : tmin;
    return ray.origin + tResult * ray.direction();
}

}
