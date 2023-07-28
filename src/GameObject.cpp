#include "GameObject.hpp"

namespace Engine
{

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _transform(position, rotation, scale) {}

void GameObject::Render(Shader* shader)
{
    this->UpdateUniforms(shader);

    for (Mesh* mesh : this->meshes)
        mesh->Render(shader);
}

bool GameObject::CollidesWith(const Ray &ray)
{
    if (!collider) return false;
    return collider->CollidesWith(ray, _transform);
}

void GameObject::UpdateUniforms(Shader* shader)
{
    shader->setMat4fv(_transform.GetMatrix(), "ModelMatrix");
}

}