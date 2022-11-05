#pragma once

#define SDL_MAIN_HANDLED

#include <assert.h>
#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>
#include "Core.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"

namespace Engine
{
    enum Shader_Enum { SHADER_CORE_PROGRAM = 0 };
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

        SDL_Window* GetWindow() { return window; }
        int GetWidth() { return frameBufferWidth; }
        int GetHeight() { return frameBufferHeight; }

        SDL_GLContext glContext;
        ImGuiContext* imguiContext;
    protected:
        //Layers
        ImGuiLayer* imGuiLayer;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        //Singleton
        static Application* application;

        //Window
        SDL_Window* window;
        
        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;
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

        //Textures
        std::vector<Texture*> textures;

        //Materials
        std::vector<Material*> materials;

        //Meshes
        std::vector<Mesh*> meshes;

        //Lights
        std::vector<glm::vec3*> lights;

        //Delta time
        float deltaTime;
        float curTime;
        float lastTime;

        //Event
        bool windowShouldClose = false;
        SDL_Event event;

        //Mouse input
        int lastMouseX;
        int lastMouseY;
        int mouseX;
        int mouseY;
        int mouseOffsetX;
        int mouseOffsetY;

        //Inits
        void InitWindow(const char* title, uint32_t windowFlags);
        void InitGLAD();
        void InitOpenGLOptions();
        void initMatrices();
        void InitShaders();
        void InitTextures();
        void InitMaterials();
        
        void InitLights();
        void InitUniforms();

        void Update();
        void UpdateDeltaTime();
        void UpdateInput();
        void UpdateMouseInput();
        void UpdateUniforms();

        void Render();
    };

    Application* CreateApplication();
}