#include "GameObject.hpp"

namespace Engine
{

    GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;

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