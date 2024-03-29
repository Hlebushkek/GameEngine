#pragma once

#define SDL_MAIN_HANDLED

#include <assert.h>
#include <iostream>
#include <SDL3/SDL.h>
#include <imgui.h>
#include "Core.hpp"
#include "Mesh.hpp"
#include "Lights.hpp"
#include "InputHandler.hpp"
#include "Camera.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"
#include "OBJLoader.hpp"

namespace MTL { class Device; class RenderPassDescriptor; class CommandQueue; }

namespace Engine
{
    class Renderer;

    enum Shader_Enum { SHADER_CORE_PROGRAM = 0, SHADER_UI_PROGRAM };
    enum Texture_Enum { GRASS = 0 , GRASS_SPECULAR, BRICK, WOOD, PAVERN, BLOCKB};
    enum Material_Enum { MAT_0 = 0 };
    enum Mesh_Enum { MESH_QUAD = 0 };

    class ENGINE_API Application
    {
    public:
        Application(const char* title, const int width, const int height);
        virtual ~Application();
        virtual void ApplicationWillTerminate() {}

        void Run();

        void AddLight(Light* light) { lights.push_back(light); }

        static Application* Get() { return application; }
        Camera* GetCamera() { return &camera; }

        SDL_Window* GetWindow() { return window; }

        float GetDeltaTime() { return deltaTime; } // Todo: move it to some kind of time class

        int GetWidth()  { return frameBufferWidth; }
        int GetHeight() { return frameBufferHeight; }

        bool IsWidnowGrabbed() { return windowGrab; }

        glm::mat4 GetViewMatrix();

    protected:
        std::shared_ptr<ImGuiLayer> imGuiLayer = nullptr;
        void PushLayer(std::shared_ptr<Layer> layer);
        void PushOverlay(std::shared_ptr<Layer> overlay);

        GameObject *hoveredObject = nullptr; //Todo: move it
        void CastRay(InputState state);

        virtual void Update();
        virtual void HandlEvents();
        virtual void UpdateUniforms();

    private:
        //Singleton
        static Application* application;

        InputHandler *inputHandler;

        //Window
        SDL_Window* window;

        bool windowGrab = false;

        bool drawOnlyWireframes = false;

        int windowWidth;
        int windowHeight;
        int frameBufferWidth;
        int frameBufferHeight;

        LayerStack layerStack;

        Camera camera;

        std::shared_ptr<Renderer> renderer;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        float fov;
        float nearPlane;
        float farPlane;

        std::vector<std::shared_ptr<Shader>> shaders;
        std::vector<Material*> materials;
        std::vector<Light*> lights;

        SDL_Event event;

        bool windowShouldClose = false;

        //Delta time
        float deltaTime;
        float curTime;
        float lastTime;

        //Inits
        void InitWindow(const char* title, uint32_t windowFlags);
        void InitMatrices();
        void InitShaders();
        void InitMaterials();

        void InitUniforms();

        void UpdateDeltaTime();
    };

    Application* CreateApplication();
}