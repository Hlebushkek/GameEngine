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

    for (size_t i = 0; i < 5; i++)
        mouseStates[i] = KEY_RELEASED;
}

void InputHandler::HandleInput(SDL_Event& event)
{
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
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (mouseStates[event.button.button] == KEY_RELEASED)
        {
            mouseStates[event.button.button] = KEY_DOWN;
            mouseStateToUpdate.push(event.button.button);
        }

        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (mouseStates[event.button.button] == KEY_HOLD)
        {
            mouseStates[event.button.button] = KEY_UP;
            mouseStateToUpdate.push(event.button.button);
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

InputState InputHandler::GetKeyState(SDL_KeyCode keycode)
{
    return GetKeyState(SDL_GetScancodeFromKey(keycode));
}

InputState InputHandler::GetKeyState(SDL_Scancode scancode)
{
    return keyStates[scancode];
}

InputState InputHandler::GetMouseButtonState(int button)
{
    return mouseStates[button];
}

std::vector<int> InputHandler::GetMouseButtonsMatchingState(InputState state)
{
    std::vector<int> indexes;

    for (size_t i = 0; i < 5; ++i)
        if (mouseStates[i] == state)
            indexes.push_back(i);

    return indexes;
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

    while (!mouseStateToUpdate.empty())
    {
        Uint8 index = mouseStateToUpdate.front();
        mouseStateToUpdate.pop();

        if (mouseStates[index] == KEY_DOWN)
            mouseStates[index] = KEY_HOLD;
        if (mouseStates[index] == KEY_UP)
            mouseStates[index] = KEY_RELEASED;
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
}

void InputHandler::HandleMouseWheelInput(SDL_Event &event)
{
    
}

}