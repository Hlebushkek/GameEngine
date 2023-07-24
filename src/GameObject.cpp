#include "GameObject.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Engine
{

const glm::vec3 GameObject::WORLD_FRONT(0.0f, 0.0f, -1.0f);
const glm::vec3 GameObject::WORLD_UP(0.0f, 1.0f, 0.0f);

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale), front(WORLD_FRONT), up(WORLD_UP), right(glm::cross(front, up))
{
    this->updateDirections();
    this->updateModelMatrix();
}

void GameObject::setPosition(const glm::vec3& position)
{
    this->position = position;
}
glm::vec3 GameObject::getPosition()
{
    return this->position;
}

void GameObject::setRotation(const glm::vec3& rotation)
{
    this->rotation = rotation;
    updateDirections();
}

void GameObject::setScale(const glm::vec3& scale)
{
    this->scale = scale;
}

void GameObject::move(const glm::vec3& position)
{
    this->position += position;
}

void GameObject::rotate(const glm::vec3& rotation)
{
    this->rotation += rotation;
    
    if (this->rotation.x > 360)
        this->rotation.x -= 360;
    if (this->rotation.y > 360)
        this->rotation.y -= 360;
    if (this->rotation.z > 360)
        this->rotation.z -= 360;

    updateDirections();
}

void GameObject::scaleUp(const glm::vec3& scale)
{
    this->scale += scale;
}

void GameObject::Render(Shader* shader)
{
    this->updateModelMatrix();
    this->updateUniforms(shader);

    for (Mesh* mesh : this->meshes)
        mesh->Render(shader);
}

void GameObject::updateUniforms(Shader* shader)
{
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}

void GameObject::updateDirections()
{
    glm::mat4 yawPitchRollRotation = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    front = glm::vec3(yawPitchRollRotation * glm::vec4(WORLD_FRONT, 0.0f));

    this->front = glm::normalize(this->front);
    this->right = glm::normalize(glm::cross(this->front, this->WORLD_UP));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}

void GameObject::updateModelMatrix()
{
    this->ModelMatrix = glm::mat4(1.0f);
    this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

}