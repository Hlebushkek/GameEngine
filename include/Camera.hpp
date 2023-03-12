#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    class Camera {
    public:
        Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
        ~Camera(){}

        const glm::mat4 getViewMatrix();

        const glm::vec3 getPosition() const;

        void move(const float& dt, const int direction);
        void updateMouseMotionInput(const float& dt, const int& offsetX, const int& offsetY);

    private:
        glm::mat4 viewMatrix;

        glm::vec3 worldUp;
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;

        GLfloat pitch;
        GLfloat yaw;
        GLfloat roll;

        GLfloat movementSpeed;
        GLfloat sensitivity;
        
        void updateCameraVectors();
    };
    
}