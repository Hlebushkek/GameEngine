#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.hpp"

namespace Engine
{
    class Camera : public GameObject {
    public:
        Camera(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.f));
        ~Camera() {}

        const glm::mat4 getViewMatrix();

        void Move(const float& dt, const int direction);
        void updateMouseMotionInput(const float& dt, const int& offsetX, const int& offsetY);

        void Update() override;

    private:
        glm::mat4 viewMatrix;

        float movementSpeed;
        float sensitivity;

    };
    
}