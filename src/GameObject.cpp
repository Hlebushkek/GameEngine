#include "GameObject.hpp"

namespace Engine
{

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _transform(position, rotation, scale), collider(nullptr) {}

void GameObject::Render(Shader* shader)
{
    this->UpdateUniforms(shader);

    for (size_t i = 0; i < this->textures.size(); i++)
        this->textures[i]->bind(i);
    for (Mesh* mesh : this->meshes)
        mesh->Render(shader);
    for (size_t i = 0; i < this->textures.size(); i++)
        this->textures[i]->unbind(i);

    if (collider)
        collider->Render(shader);
}

std::optional<Intersection> GameObject::CollidesWith(const Ray &ray)
{
    if (!collider) return std::nullopt;

    auto result = collider->CollidesWith(ray, _transform);
    if (result.has_value())
        return std::optional<Intersection>{{result.value(), this}};

    return std::nullopt;
}

void GameObject::UpdateUniforms(Shader* shader)
{
    shader->setMat4fv(_transform.GetMatrix(), "ModelMatrix");
    shader->set1i(this->textures.size() > 0, "isTextureBound");
}

}