#include "GameObject.hpp"

namespace Engine
{

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _transform(position, rotation, scale), collider(nullptr) {}

void GameObject::Render(Shader* shader)
{
    this->UpdateUniforms(shader);

    for (Mesh* mesh : this->meshes)
        mesh->Render(shader);

    if (collider)
        collider->Render(shader);
}

std::optional<Intersection> GameObject::CollidesWith(const Ray &ray)
{
    if (!collider) return std::nullopt;

    auto result = collider->CollidesWith(ray, _transform);
    if (result.has_value())
    {
        OnRayIntersection(ray);
        return std::optional<Intersection>{{result.value(), this}};
    }

    return std::nullopt;
}

void GameObject::UpdateUniforms(Shader* shader)
{
    shader->setMat4fv(_transform.GetMatrix(), "ModelMatrix");
}

}