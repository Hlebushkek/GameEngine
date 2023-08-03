#pragma once

#include <queue>
#include <vector>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "Core.hpp"

namespace Engine
{

enum InputState
{
    KEY_RELEASED = 0,
    KEY_DOWN = 1 << 0,
    KEY_HOLD = 1 << 1,
    KEY_UP = 1 << 2
};

class ENGINE_API InputHandler
{
public:
    virtual ~InputHandler() = default;

    static InputHandler* Get()
    {
        if (!instance)
            instance = new InputHandler();
        return instance;
    }

    void HandleInput(SDL_Event& event);

    InputState GetKeyState(SDL_KeyCode key);
    InputState GetKeyState(SDL_Scancode key);
    
    InputState GetMouseButtonState(int button);
    std::vector<int> GetMouseButtonsMatchingState(InputState state);

    void Reset();

    bool MouseMoved() { return mouseMoved; }
    glm::vec3 GetMouseDeltaOffset() { return glm::vec3(mouseOffsetX, mouseOffsetY, 0); }
    glm::vec3 GetMousePosition() { return glm::vec3(mouseX, mouseY, 0); }

private:
    //Singleton
    InputHandler();
    static InputHandler* instance;

    void HandleMouseMotionInput(SDL_Event& event);
    void HandleMouseWheelInput(SDL_Event& event);

    InputState keyStates[512];
    InputState mouseStates[5];

    std::queue<SDL_Scancode> keyStateToUpdate;
    std::queue<Uint8> mouseStateToUpdate;

    //Mouse input
    bool mouseMoved;

    float lastMouseX;
    float lastMouseY;
    float mouseX;
    float mouseY;

    float mouseOffsetX;
    float mouseOffsetY;

};

}