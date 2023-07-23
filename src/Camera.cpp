#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Application.hpp"
#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Vertex.hpp"

namespace Engine
{
    Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
    {
        this->viewMatrix = glm::mat4(1.f);

        this->movementSpeed = 2.f;
        this->sensitivity = 200.f;

        this->worldUp = worldUp;
        this->position = position;
        this->right = glm::vec3(0.f);
        this->up = worldUp;

        this->pitch = 0.f;
        this->yaw = -90.f;
        this->roll = 0.f;

        this->updateCameraVectors();
    }

    void Camera::Update(float dt)
    {
        auto handler = InputHandler::Get();

        if (handler->GetKeyState(SDLK_w) == KEY_DOWN || handler->GetKeyState(SDLK_w) == KEY_HOLD)
            this->move(dt, FORWARD);
        if (handler->GetKeyState(SDLK_s) == KEY_DOWN || handler->GetKeyState(SDLK_s) == KEY_HOLD)
            this->move(dt, BACKWARD);
        if (handler->GetKeyState(SDLK_a) == KEY_DOWN || handler->GetKeyState(SDLK_a) == KEY_HOLD)
            this->move(dt, LEFT);
        if (handler->GetKeyState(SDLK_d) == KEY_DOWN || handler->GetKeyState(SDLK_d) == KEY_HOLD)
            this->move(dt, RIGHT);
        if (handler->GetKeyState(SDLK_SPACE) == KEY_DOWN || handler->GetKeyState(SDLK_SPACE) == KEY_HOLD)
            this->move(dt, UP);
        if (handler->GetKeyState(SDLK_c) == KEY_DOWN || handler->GetKeyState(SDLK_DOWN) == KEY_HOLD)
            this->move(dt, DOWN);

        if (handler->MouseMoved() && Application::Get()->IsWidnowGrabbed())
        {
            glm::vec3 mouseOffset = handler->GetMouseDeltaOffset();
            updateMouseMotionInput(dt, mouseOffset.x, mouseOffset.y);
        }
    }

    void Camera::updateCameraVectors()
    {
        this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->front.y = sin(glm::radians(this->pitch));
        this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

        this->front = glm::normalize(this->front);
        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));
    }

    void Camera::move(const float& dt, const int direction)
    {
        switch (direction)
        {
        case FORWARD:
            this->position += this->front * this->movementSpeed * dt;
            break;
        case BACKWARD:
            this->position -= this->front * this->movementSpeed * dt;
            break;
        case LEFT:
            this->position -= this->right * this->movementSpeed * dt;
            break;
        case RIGHT:
            this->position += this->right * this->movementSpeed * dt;
            break;
        case UP:
            this->position += this->up * this->movementSpeed * dt;
            break;
        case DOWN:
            this->position -= this->up * this->movementSpeed * dt;
            break;
        default:
            break;
        }
    }

    void Camera::updateMouseMotionInput(const float& dt, const int& offsetX, const int& offsetY)
    {
        this->pitch -= static_cast<GLfloat>(offsetY * this->sensitivity * dt);
        this->yaw += static_cast<GLfloat>(offsetX * this->sensitivity * dt);

        if (this->pitch >= 80.f)
            this->pitch = 80.f;
        else if (this->pitch < -80.f)
            this->pitch = -80.f;

        if (this->yaw >= 360.f || this->yaw < -360.f)
            this->yaw = 0.f;
    }

    const glm::mat4 Camera::getViewMatrix()
    {
        this->updateCameraVectors();
        // std::cout << "Camera pos: " << glm::to_string(position) << std::endl;
        this->viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

        return this->viewMatrix;
    }

    const glm::vec3 Camera::getPosition() const
    {
        return this->position;
    }
    
}