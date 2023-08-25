#pragma once

#include <iostream>
#include <array>
#include <vector>
#include "Core.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Collider.hpp"
#include "Ray.hpp"
#include "Transform.hpp"
#include "Intersection.hpp"

namespace Engine
{

class ENGINE_API GameObject : std::enable_shared_from_this<GameObject>
{
public:
    GameObject(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
    virtual ~GameObject() {}

    template <typename T, typename... Args>
    static std::shared_ptr<T> Instantiate(Args&&... args) {
        std::shared_ptr<T> instance = std::make_shared<T>(std::forward<Args>(args)...);
        instance->Initialize(instance);
        return instance;
    }

    std::shared_ptr<Transform> transform() { return m_transform; }

    void AddMesh(Mesh *mesh) { this->meshes.push_back(mesh); }
    void AddTexture(Texture *texture) { this->textures.push_back(texture); }
    void SetTexture(Texture *texture, size_t index)
    {
        if (textures.size() <= index)
            this->textures.push_back(texture);
        else
            this->textures[index] = texture;
    }
    void RemoveTextureAt(size_t index)
    {
        if (textures.size() != 0 && index >= 0 && index < textures.size())
            textures.erase(textures.begin() + index);
    }

    //Virtual
    virtual void Initialize(std::shared_ptr<GameObject> object);
    
    virtual void Render(Shader* shader);
    virtual void Update() {}
    virtual std::optional<Intersection> CollidesWith(const Ray& ray);

    virtual void OnAttach() {}

    virtual void OnMouseEnter() {}
    virtual void OnMouseExit() {}
    virtual void OnMouseDown(int button) {}
    virtual void OnMouseUp(int button) {}

protected:
    std::shared_ptr<Transform> m_transform;
    Collider *collider;
    std::vector<Mesh*> meshes;
    std::vector<Texture*> textures;
    
    void UpdateUniforms(Shader* shader);
};

}
