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

class ENGINE_API GameObject
{
public:
    GameObject(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
    virtual ~GameObject() {}

    Transform& transform() { return _transform; }
    std::optional<Intersection> CollidesWith(const Ray& ray);

    void SetMesh(Mesh *mesh) { this->meshes.push_back(mesh); }

    //Virtual
    virtual void Render(Shader* shader);
    virtual void Update() {}
    virtual void OnRayIntersection(const Ray& ray) {}

protected:
    Transform _transform;
    Collider *collider;
    std::vector<Mesh*> meshes;
    
    void UpdateUniforms(Shader* shader);
};

}
