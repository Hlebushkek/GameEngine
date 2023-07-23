#include <iostream>
#include "InputHandler.hpp"

namespace Engine
{

InputHandler *InputHandler::instance = nullptr;

InputHandler::InputHandler()
{
    keyStateToUpdate = std::queue<SDL_Scancode>();

    for (size_t i = 0; i < 512; i++)
        keyStates[i] = KEY_RELEASED;
}

void InputHandler::HandleInput(SDL_Event& event)
{
    std::cout << "Event: "<< event.type << std::endl;
    SDL_Scancode code = event.key.keysym.scancode;
    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
        if (keyStates[code] == KEY_RELEASED)
        {
            keyStates[code] = KEY_DOWN;
            keyStateToUpdate.push(code);
        }

        break;
    case SDL_EVENT_KEY_UP:
        if (keyStates[code] == KEY_HOLD)
        {
            keyStates[code] = KEY_UP;
            keyStateToUpdate.push(code);
        }

        break;
    case SDL_EVENT_MOUSE_MOTION:
        HandleMouseMotionInput(event);
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        HandleMouseWheelInput(event);
        break;
    }
}

KeyState InputHandler::GetKeyState(SDL_KeyCode keycode)
{
    return GetKeyState(SDL_GetScancodeFromKey(keycode));
}

KeyState InputHandler::GetKeyState(SDL_Scancode scancode)
{
    return keyStates[scancode];
}

bool InputHandler::IsMouseButtonPressed(int button)
{
    return false;
}

void InputHandler::Reset()
{
    mouseMoved = false;

    while (!keyStateToUpdate.empty())
    {
        SDL_Scancode code = keyStateToUpdate.front();
        keyStateToUpdate.pop();

        if (keyStates[code] == KEY_DOWN)
            keyStates[code] = KEY_HOLD;
        if (keyStates[code] == KEY_UP)
            keyStates[code] = KEY_RELEASED;
    }
}

void InputHandler::HandleMouseMotionInput(SDL_Event &event)
{
    mouseMoved = true;

    SDL_GetMouseState(&mouseX, &mouseY);
    
    this->mouseOffsetX = event.motion.xrel;
    this->mouseOffsetY = event.motion.yrel;
    
    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;

    // std::cout << mouseOffsetX << " " << mouseOffsetY << std::endl;
}

void InputHandler::HandleMouseWheelInput(SDL_Event &event)
{
    
}

}