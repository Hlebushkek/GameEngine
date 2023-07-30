#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Application.hpp"
#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Vertex.hpp"

namespace Engine
{
    Camera::Camera(glm::vec3 position, glm::vec3 rotation)
        : GameObject(position, rotation)
    {
        this->viewMatrix = glm::mat4(1.f);

        this->movementSpeed = 2.f;
        this->sensitivity = 150.f;
    }

    void Camera::Update()
    {
        auto handler = InputHandler::Get();
        auto app = Application::Get();
        float dt = app->GetDeltaTime();

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
        if (handler->GetKeyState(SDLK_c) == KEY_DOWN || handler->GetKeyState(SDLK_c) == KEY_HOLD)
            this->move(dt, DOWN);
        if (handler->GetKeyState(SDLK_LSHIFT) == KEY_DOWN || handler->GetKeyState(SDLK_LSHIFT) == KEY_HOLD)
            this->movementSpeed = 0.8f;
        else 
            this->movementSpeed = 2.f;

        if (handler->MouseMoved() && Application::Get()->IsWidnowGrabbed())
        {
            glm::vec3 mouseOffset = handler->GetMouseDeltaOffset();
            updateMouseMotionInput(dt, mouseOffset.x, mouseOffset.y);
        }
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
        this->rotation.x -= static_cast<GLfloat>(offsetY * this->sensitivity * dt);
        this->rotation.y -= static_cast<GLfloat>(offsetX * this->sensitivity * dt);

        if (this->rotation.x >= 80.f)
            this->rotation.x = 80.f;
        else if (this->rotation.x < -80.f)
            this->rotation.x = -80.f;

        if (this->rotation.y >= 360.f || this->rotation.y < -360.f)
            this->rotation.y = 0.f;

        this->updateDirections();
    }

    const glm::mat4 Camera::getViewMatrix()
    {
        this->viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
        return this->viewMatrix;
    }

    const glm::vec3 Camera::getPosition() const
    {
        return this->position;
    }
    
}