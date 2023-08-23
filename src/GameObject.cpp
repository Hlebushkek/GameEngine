#include "GameObject.hpp"

namespace Engine
{

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : m_transform(std::make_shared<Transform>(position, rotation, scale)), collider(nullptr) {}

void GameObject::Initialize(std::shared_ptr<GameObject> object)
{
    m_transform->SetObject(object);
}

void GameObject::Render(Shader *shader)
{
    this->UpdateUniforms(shader);

    for (size_t i = 0; i < this->textures.size(); i++)
        this->textures[i]->bind(i);
    for (Mesh* mesh : this->meshes)
        mesh->Render(shader);
    for (auto weakTransform : transform()->GetChildren())
        if (auto transform = weakTransform.lock())
            if (auto obj = transform->gameObject().lock())
                obj->Render(shader);
    for (size_t i = 0; i < this->textures.size(); i++)
        this->textures[i]->unbind(i);

    if (collider)
        collider->Render(shader);
}

std::optional<Intersection> GameObject::CollidesWith(const Ray &ray)
{
    if (!collider) return std::nullopt;

    auto result = collider->CollidesWith(ray, m_transform);
    if (result.has_value())
        return std::optional<Intersection>{{result.value(), this}};

    return std::nullopt;
}

void GameObject::UpdateUniforms(Shader* shader)
{
    shader->setMat4fv(m_transform->GetMatrix(), "ModelMatrix");
    shader->set1i(this->textures.size() > 0, "isTextureBound");
}

}