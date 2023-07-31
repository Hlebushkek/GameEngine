#pragma once

#define SDL_MAIN_HANDLED

#include <assert.h>
#include <iostream>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>
#include "Core.hpp"
#include "Mesh.hpp"
#include "InputHandler.hpp"
#include "Camera.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"
#include "OBJLoader.hpp"
#include "Button.hpp"

namespace Engine
{
    enum Shader_Enum { SHADER_CORE_PROGRAM = 0, SHADER_UI_PROGRAM };
    enum Texture_Enum { GRASS = 0 , GRASS_SPECULAR, BRICK, WOOD, PAVERN, BLOCKB};
    enum Material_Enum { MAT_0 = 0 };
    enum Mesh_Enum { MESH_QUAD = 0 };

    class ENGINE_API Application
    {
    public:
        Application(const char* title, const int width, const int height);
        virtual ~Application();
        void Run();

        static Application* Get() { return application; }
        Camera* GetCamera() { return &camera; }

        SDL_Window* GetWindow() { return window; }
        SDL_GLContext& GetGLContext() { return glContext; }
        float GetDeltaTime() { return deltaTime; } // Todo: move it to some kind of time class

        int GetWidth() { return frameBufferWidth; }
        int GetHeight() { return frameBufferHeight; }

        bool IsWidnowGrabbed() { return windowGrab; }

        glm::mat4 GetViewMatrix();

    protected:
        //Layers
        ImGuiLayer* imGuiLayer;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        //Singleton
        static Application* application;

        InputHandler *inputHandler;

        //Window
        SDL_Window* window;
        SDL_GLContext glContext;
        bool windowGrab = false;

        bool drawOnlyWireframes = false;

        int windowWidth;
        int windowHeight;
        int frameBufferWidth;
        int frameBufferHeight;

        //Layers
        LayerStack layerStack;

        //Camera
        Camera camera;

        //Matrices
        glm::mat4 viewMatrix;
        glm::vec3 camPosition;
        glm::vec3 worldUp;
        glm::vec3 camFront;

        glm::mat4 projectionMatrix;
        float fov;
        float nearPlane;
        float farPlane;

        //Shaders
        std::vector<Shader*> shaders;

        //Materials
        std::vector<Material*> materials;

        //Meshes
        std::vector<Mesh*> meshes;

        //Lights
        std::vector<glm::vec3*> lights;

        //Event
        SDL_Event event;

        bool windowShouldClose = false;

        //Delta time
        float deltaTime;
        float curTime;
        float lastTime;

        //Inits
        void InitWindow(const char* title, uint32_t windowFlags);
        void InitGLAD();
        void InitOpenGLOptions();
        void initMatrices();
        void InitShaders();
        void InitMaterials();
        
        void InitLights();
        void InitUniforms();

        void CastRay();

        void Update();
        void UpdateDeltaTime();
        void HandlEvents();
        void UpdateUniforms();
    };

    Application* CreateApplication();
}