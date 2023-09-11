#include "Renderer.hpp"
#include "Shader.hpp"
#include "ShaderTypesCommon.h"
#include "Mesh.hpp"
#include "GameObject.hpp"

namespace Engine
{

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
: m_transform(std::make_shared<Transform>(position, rotation, scale)), collider(nullptr) {}

void GameObject::Initialize(std::shared_ptr<GameObject> object)
{
    m_transform->SetObject(object);
}

void GameObject::Render(Renderer* renderer, Shader* shader)
{
    for (size_t i = 0; i < this->textures.size(); i++)
        if (this->textures[i])
            this->textures[i]->Bind(i);
    for (auto mesh : this->meshes)
        mesh->Render(shader, {m_transform->GetMatrix(), this->textures.size() > 0});
    for (auto weakTransform : transform()->GetChildren())
        if (auto transform = weakTransform.lock())
            if (auto obj = transform->gameObject().lock())
                obj->Render(renderer, shader);
    for (size_t i = 0; i < this->textures.size(); i++)
        if (this->textures[i])
            this->textures[i]->Unbind();
    
    // if (collider)
    //     collider->Render(renderer);
}

std::optional<Intersection> GameObject::CollidesWith(const Ray &ray)
{
    if (!collider) return std::nullopt;
    
    auto result = collider->CollidesWith(ray, m_transform);
    if (result.has_value())
        return std::optional<Intersection>{{result.value(), this}};
    
    return std::nullopt;
}

}
