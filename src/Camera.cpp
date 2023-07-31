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
            this->Move(dt, FORWARD);
        if (handler->GetKeyState(SDLK_s) == KEY_DOWN || handler->GetKeyState(SDLK_s) == KEY_HOLD)
            this->Move(dt, BACKWARD);
        if (handler->GetKeyState(SDLK_a) == KEY_DOWN || handler->GetKeyState(SDLK_a) == KEY_HOLD)
            this->Move(dt, LEFT);
        if (handler->GetKeyState(SDLK_d) == KEY_DOWN || handler->GetKeyState(SDLK_d) == KEY_HOLD)
            this->Move(dt, RIGHT);
        if (handler->GetKeyState(SDLK_SPACE) == KEY_DOWN || handler->GetKeyState(SDLK_SPACE) == KEY_HOLD)
            this->Move(dt, UP);
        if (handler->GetKeyState(SDLK_c) == KEY_DOWN || handler->GetKeyState(SDLK_c) == KEY_HOLD)
            this->Move(dt, DOWN);

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

    void Camera::Move(const float& dt, const int direction)
    {
        switch (direction)
        {
        case FORWARD:
            _transform.Move( _transform.GetFront() * movementSpeed * dt);
            break;
        case BACKWARD:
            _transform.Move(-_transform.GetFront() * movementSpeed * dt);
            break;
        case LEFT:
            _transform.Move(-_transform.GetRight() * movementSpeed * dt);
            break;
        case RIGHT:
            _transform.Move( _transform.GetRight() * movementSpeed * dt);
            break;
        case UP:
            _transform.Move( _transform.GetUp()    * movementSpeed * dt);
            break;
        case DOWN:
            _transform.Move(-_transform.GetUp()    * movementSpeed * dt);
            break;
        default:
            break;
        }
    }

    void Camera::updateMouseMotionInput(const float& dt, const int& offsetX, const int& offsetY)
    {
        _transform.Rotate({
            -static_cast<GLfloat>(offsetY * this->sensitivity * dt),
            -static_cast<GLfloat>(offsetX * this->sensitivity * dt),
            0
        });

        glm::vec3 rotation = _transform.GetRotation();
        if (rotation.x >= 80.f)
            _transform.SetRotation({ 80.f, rotation.y, 0 });
        else if (rotation.x < -80.f)
            _transform.SetRotation({-80.f, rotation.y, 0 });

        rotation = _transform.GetRotation();
        if (rotation.y >= 360.f || rotation.y < -360.f)
            _transform.SetRotation({ rotation.x, 0, 0 });
    }

    const glm::mat4 Camera::getViewMatrix()
    {
        this->viewMatrix = glm::lookAt(_transform.GetPosition(), _transform.GetPosition() + _transform.GetFront(), _transform.GetUp());
        return this->viewMatrix;
    }
    
}