#pragma once

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Engine
{

class GameObject; 

class Transform {
public:
    Transform(GameObject *gameObject, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f))
        : position(position), rotation(rotation), scale(scale), m_GameObject(gameObject)
    {
        front = WORLD_FRONT;
        up = WORLD_UP;
        right = glm::cross(front, up);

        UpdateDirections();
    }

    void SetPosition(const glm::vec3& pos) { position = pos; }
    void SetRotation(const glm::vec3& rot) { rotation = rot; UpdateDirections(); }
    void SetScale(const glm::vec3& scl) { scale = scl; }

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetRotation() const { return rotation; }
    glm::vec3 GetScale() const { return scale; }

    void Move(const glm::vec3& position) { this->position += position; }
    void Rotate(const glm::vec3& rotation)
    {
        this->rotation += rotation;
        
        if (this->rotation.x > 360)
            this->rotation.x -= 360;
        if (this->rotation.y > 360)
            this->rotation.y -= 360;
        if (this->rotation.z > 360)
            this->rotation.z -= 360;

        UpdateDirections();
    }
    void ScaleUp(const glm::vec3& scale) { this->scale *= scale; }

    glm::vec3 GetFront() const { return front; }
    glm::vec3 GetUp() const { return up; }
    glm::vec3 GetRight() const { return right; }

    glm::mat4 GetMatrix() const;

    void UpdateDirections();

    void SetParent(Transform* newParent)
    {
        if (parent != nullptr) parent->RemoveChild(this); 
        parent = newParent;
        if (parent != nullptr) parent->AddChild(this);
        
    }

    Transform* GetParent() const 
    {
        return parent;
    }

    const std::vector<Transform*>& GetChildren() const
    {
        return children;
    }

    GameObject* gameObject() const { return m_GameObject; }

    static const glm::vec3 WORLD_FRONT; // Todo: move it to some kind of world settings class
    static const glm::vec3 WORLD_UP; // Todo: move it to some kind of world settings class

private:
    void AddChild(Transform* child)
    {
        child->SetParent(this);
        children.push_back(child);
    }

    void RemoveChild(Transform* child) 
    {
        child->SetParent(nullptr);
        children.erase(std::remove(children.begin(), children.end(), child), children.end());
    }

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    Transform* parent;
    std::vector<Transform*> children;

    GameObject* m_GameObject;
};

}