#include "../include/Application.hpp"

namespace Engine
{
    Application::Application(const char* title, const int width, const int height) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height)
    {
        this->initWindow(title, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        this->initGLAD();
        this->initOpenGLOptions();
    }

    Application::~Application(){}

    void Application::Run()
    {
        std::cout << "Applicaton satrt Running" << std::endl;
        while(!this->windowShouldClose)
        {
            this->update();
        }
        std::cout << "Applicaton end Running" << std::endl;
    }

    void Application::initWindow(const char* title, uint32_t windowFlags)
    {
        window = SDL_CreateWindow(title, 400, 400, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);
        assert(this->window);

        // SDL_GetWindowSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
        SDL_GL_CreateContext(this->window);

        // SDL_ShowCursor(SDL_DISABLE);
        // SDL_SetRelativeMouseMode(SDL_TRUE);

        SDL_PumpEvents();
        // SDL_GetMouseState(&lastMouseX, &lastMouseY);
        // SDL_GetMouseState(&mouseX, &mouseY);
    }

    void Application::initGLAD()
    {
        int status = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
        assert(status);
    }

    void Application::initOpenGLOptions()
    {
        // glEnable(GL_DEPTH_TEST);

        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        // glFrontFace(GL_CCW);
        
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void Application::updateInput()
    {
        while (SDL_PollEvent(&event))
        {
            // updateMouseInput();
            std::cout << event.type << std::endl;
            if (event.type == SDL_KEYDOWN)
            {
                // this->updateKeyboardInput();
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                // this->updateWheelInput();
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                // this->camera.updateMouseMotionInput(deltaTime, this->mouseOffsetX, this->mouseOffsetY);
            }
            else if (event.type == SDL_QUIT)
            {
                this->windowShouldClose = true;
            }
        }
    }

    void Application::update()
    {
        //Update deltaTime
        // this->updateDeltaTime();
        //Update input
        SDL_GetWindowSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
        glViewport(0, 0, this->frameBufferWidth, this->frameBufferHeight);
        glClearColor(0.2, 0.2, 0.2, 1);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        this->updateInput();

        SDL_GL_SwapWindow(window);

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

