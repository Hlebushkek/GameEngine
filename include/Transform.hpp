#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Core.hpp"

namespace Engine
{

class GameObject; 

class ENGINE_API Transform : public std::enable_shared_from_this<Transform>
{
public:
    Transform(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f))
        : position(position), rotation(rotation), scale(scale)
    {
        front = WORLD_FRONT;
        up = WORLD_UP;
        right = glm::cross(front, up);

        UpdateDirections();
    }

    void SetObject(std::weak_ptr<GameObject> object) { m_gameObject = object; }

    void SetPosition(const glm::vec3& pos) { position = pos; }
    void SetRotation(const glm::vec3& rot) { rotation = rot; UpdateDirections(); }
    void SetScale(const glm::vec3& scl) { scale = scl; }

    const glm::vec3 GetPosition() const { return position; }
    const glm::vec3 GetRotation() const { return rotation; }
    const glm::vec3 GetScale() const { return scale; }

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

    void SetParent(std::weak_ptr<Transform> parent);
    void UnassignParent();

    std::weak_ptr<Transform> GetParent() const { return m_parent; }
    const std::vector<std::weak_ptr<Transform>>& GetChildren() const { return m_children; }

    std::weak_ptr<GameObject> gameObject() const { return m_gameObject; }

    static const glm::vec3 WORLD_FRONT; // Todo: move it to some kind of world settings class
    static const glm::vec3 WORLD_UP; // Todo: move it to some kind of world settings class

private:
    void AddChild(std::weak_ptr<Transform> child)
    {
        m_children.push_back(child);
    }

    void RemoveChild(std::shared_ptr<Transform> child) 
    {
        m_children.erase(
            std::remove_if(m_children.begin(), m_children.end(),
                [&](const std::weak_ptr<Transform>& wp) {
                    if (auto sp = wp.lock()) {
                        return sp == child;
                    }
                    return false;
                }
            ),
            m_children.end()
        );
    }

    std::weak_ptr<GameObject> m_gameObject;
    std::weak_ptr<Transform> m_parent;
    std::vector<std::weak_ptr<Transform>> m_children;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
};

}