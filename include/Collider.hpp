#pragma once

#include <optional>
#include "Core.hpp"
#include "Ray.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"

namespace Engine
{

class ENGINE_API Collider
{
public:
    virtual std::optional<glm::vec3> CollidesWith(const Ray& ray, std::shared_ptr<Transform> transform) = 0;
    virtual void Render(Shader *shader) { if (mesh) { mesh->Render(shader); } }

protected:
    Mesh *mesh = nullptr;

};

}