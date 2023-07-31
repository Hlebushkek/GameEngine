#include "Transform.hpp"

namespace Engine
{

const glm::vec3 Transform::WORLD_FRONT(0.0f, 0.0f, -1.0f);
const glm::vec3 Transform::WORLD_UP(0.0f, 1.0f, 0.0f);

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 matrix(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, scale);
    return matrix;
}

void Transform::UpdateDirections()
{
    glm::mat4 yawPitchRollRotation = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    front = glm::vec3(yawPitchRollRotation * glm::vec4(WORLD_FRONT, 0.0f));

    this->front = glm::normalize(this->front);
    this->right = glm::normalize(glm::cross(this->front, this->WORLD_UP));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}

}