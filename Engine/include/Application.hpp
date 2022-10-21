#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <assert.h>
#include <iostream>
#include "Core.hpp"

namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application(const char* title, const int width, const int height);
        virtual ~Application();
        void Run();

    private:

        //Window
        SDL_Window* window;
        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;
        int frameBufferWidth;
        int frameBufferHeight;

        //Event
        bool windowShouldClose = false;
        SDL_Event event;

        //Inits
        void initWindow(const char* title, uint32_t windowFlags);
        void initGLAD();
        void initOpenGLOptions();

        void update();
        void updateInput();
    };

    Application* CreateApplication();
}