#include <glm/gtx/string_cast.hpp>
#include "Application.hpp"
#include "Renderer.hpp"
#include "ShaderTypesCommon.h"
#include "Ray.hpp"
#include "Rect.hpp"
#include "Cube.hpp"

namespace Engine
{
    Application* Application::application = nullptr;

    Application::Application(const char* title, const int width, const int height)
        : windowWidth(width), windowHeight(height), camera(glm::vec3(0.f, 0.f, 1.f))
    {
        this->window = nullptr;
        this->frameBufferWidth = this->windowWidth;
        this->frameBufferHeight = this->windowHeight;

        this->fov = 90.f;
        this->nearPlane = 0.01f;
        this->farPlane = 1000.f;

#ifdef ENABLE_METAL
        this->InitWindow(title, SDL_WINDOW_METAL | SDL_WINDOW_RESIZABLE);
#else
        this->InitWindow(title, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
#endif
        renderer = std::make_shared<Renderer>(window);

        this->InitMatrices();
        this->InitShaders();
        this->InitMaterials();
        this->InitUniforms();

        application = this;

        inputHandler = InputHandler::Get();

        imGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(imGuiLayer);
        std::cout << "End App constructor" << std::endl;
    }

    Application::~Application()
    {
        SDL_DestroyWindow(this->window);
        
        for (size_t i = 0; i < this->materials.size(); i++)
            delete this->materials[i];
    }

    void Application::Run()
    {
        while(!this->windowShouldClose)
            this->Update();
    }

    void Application::InitWindow(const char* title, uint32_t windowFlags)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        window = SDL_CreateWindow(title, windowWidth, windowHeight, windowFlags);
        assert(this->window);

        SDL_GetWindowSize(this->window, &this->windowWidth, &this->windowHeight);
        SDL_GetWindowSizeInPixels(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

        SDL_PumpEvents();
    }

    void Application::InitMatrices()
    {
        this->viewMatrix = GetViewMatrix();

        this->projectionMatrix = glm::mat4(1.f);
        this->projectionMatrix = glm::perspective(glm::radians(this->fov),
            static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
            this->nearPlane, this->farPlane);
    }

    void Application::InitShaders()
    {
#ifdef ENABLE_METAL
        shaders.emplace_back(std::make_shared<Shader>("Shaders.metal"));
#else
        shaders.emplace_back(std::make_shared<Shader>("vertex_shader.glsl", "fragment_shader.glsl"));
        shaders.emplace_back(std::make_shared<Shader>("ui_vertex_shader.glsl", "fragment_shader.glsl"));
#endif
    }

    void Application::InitMaterials()
    {
        this->materials.push_back(new Material{glm::vec3(0.1f), glm::vec3(10.f), glm::vec3(1.f)});
    }

    void Application::InitUniforms()
    {
        shaders[SHADER_CORE_PROGRAM]->SetFrameData({viewMatrix, projectionMatrix, camera.transform()->GetPosition(),
            (unsigned)frameBufferWidth, (unsigned)frameBufferHeight});
        shaders[SHADER_CORE_PROGRAM]->SetLights({});
    }

    void Application::PushLayer(std::shared_ptr<Layer> layer)
    {
        layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(std::shared_ptr<Layer> overlay)
    {
        layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Update()
    {
        UpdateDeltaTime();
        HandlEvents();
        UpdateUniforms();

        camera.Update();

        shaders[SHADER_CORE_PROGRAM]->SetMaterial(*materials[MAT_0]);
        // shaders[SHADER_UI_PROGRAM]->SetMaterial(*materials[MAT_0]);

        renderer->PreRenderSetup();
        {
            for (const auto& layer : layerStack)
            {
                layer->Update();
                layer->Render(renderer.get(), shaders[SHADER_CORE_PROGRAM].get());
            }

            // for (const auto& layer : layerStack)
            //     layer->RenderUI(this->shaders[SHADER_UI_PROGRAM]);

            renderer->PreImGuiRenderSetup();
            {
                for (const auto& layer : layerStack)
                    layer->OnImGuiRender();
            }
            renderer->PostImGuiRenderSetup();
        }
        renderer->PostRenderSetup();
    }

    void Application::HandlEvents()
    {
        this->inputHandler->Reset();
        
        while (SDL_PollEvent(&event))
        {
            this->imGuiLayer->OnEvent(event);
            this->inputHandler->HandleInput(event);

            if (event.type == SDL_EVENT_QUIT)
            {
                ApplicationWillTerminate();
                this->windowShouldClose = true;
            }
        }

        if (inputHandler->GetKeyState(SDLK_ESCAPE) == KEY_DOWN)
        {
            SDL_Event event;
            event.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&event);
        }

        if (inputHandler->GetKeyState(SDLK_e) == KEY_DOWN)
        {
            windowGrab = !windowGrab;
            SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
            SDL_SetRelativeMouseMode((SDL_bool)this->windowGrab);
        }

        if (inputHandler->GetKeyState(SDLK_y) == KEY_DOWN)
        {
            drawOnlyWireframes = !drawOnlyWireframes;
            renderer->SetOnlyWireframeMode(drawOnlyWireframes);
        }

        this->CastRay(KEY_RELEASED);
        this->CastRay(KEY_DOWN);
        this->CastRay(KEY_UP);
    }

    void Application::CastRay(InputState state)
    {
        std::vector<int> buttons = inputHandler->GetMouseButtonsMatchingState(state);
        if (buttons.size() <= 0)
            return;

        glm::vec3 sdlMousePos = inputHandler->GetMousePosition();

        float ndcX = (2.0f * sdlMousePos.x) / windowWidth - 1.0f;
        float ndcY = 1.0f - (2.0f * sdlMousePos.y) / windowHeight;

        glm::mat4 viewMatrix = GetViewMatrix();
        glm::mat4 viewProjectionInverse = glm::inverse(projectionMatrix * viewMatrix);

        glm::vec4 rayStartNDC(ndcX, ndcY, -1.0, 1.0);
        glm::vec4 rayEndNDC(ndcX, ndcY, 0.0, 1.0);

        glm::vec4 rayStartWorld = viewProjectionInverse * rayStartNDC;
        glm::vec4 rayEndWorld = viewProjectionInverse * rayEndNDC;

        rayStartWorld /= rayStartWorld.w;
        rayEndWorld /= rayEndWorld.w;

        Ray mouseRay { glm::vec3(rayStartWorld), glm::vec3(rayEndWorld) };
        for (auto layer : layerStack) //Todo: Think about layers and raycast
        {
            auto intersection = layer->CheckRayCast(mouseRay, buttons);
            if (intersection.has_value())
            {
                switch (state)
                {
                case InputState::KEY_DOWN:
                    for (auto& button : buttons)
                        intersection.value().object->OnMouseDown(button);
                    break;
                case InputState::KEY_UP:
                    for (auto& button : buttons)
                        intersection.value().object->OnMouseUp(button);
                    break;
                case InputState::KEY_RELEASED:
                    if (!this->hoveredObject)
                    {
                        this->hoveredObject = intersection.value().object;
                        intersection.value().object->OnMouseEnter();
                    }
                    else if (intersection.value().object != this->hoveredObject)
                    {
                        this->hoveredObject->OnMouseExit();
                        intersection.value().object->OnMouseEnter();
                        this->hoveredObject = intersection.value().object;
                    }
                    break;
                default: break;
                }
                // std::cout << "Ray intersected with game object: " << intersection.value().object << std::endl;
                // //Draw ray gizmo
                // std::cout << "Ray: " << glm::to_string(mouseRay.origin) << ", direction: " << glm::to_string(mouseRay.direction()) << std::endl;
                break;
            }
            else
            {
                if (state == KEY_RELEASED && this->hoveredObject)
                {
                    this->hoveredObject->OnMouseExit();
                    this->hoveredObject = nullptr;
                }
            }
        }
    }

    void Application::UpdateDeltaTime()
    {
        Uint64 ticks = SDL_GetTicks();
        this->curTime = static_cast<float>(ticks) / 1000.;
        this->deltaTime = this->curTime - this->lastTime;
        this->lastTime = this->curTime;
    }

    void Application::UpdateUniforms()
    {
        SDL_GetWindowSize(this->window, &this->windowWidth, &this->windowHeight);
        SDL_GetWindowSizeInPixels(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

        this->viewMatrix = this->camera.getViewMatrix();

        this->projectionMatrix = glm::mat4(1.f);
        this->projectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
            this->nearPlane, this->farPlane);

        shaders[SHADER_CORE_PROGRAM]->SetFrameData({viewMatrix, projectionMatrix, camera.transform()->GetPosition(),
            (unsigned)frameBufferWidth, (unsigned)frameBufferHeight});

        shaders[SHADER_CORE_PROGRAM]->SetLights(lights);
    }
    
    glm::mat4 Application::GetViewMatrix() { return this->camera.getViewMatrix(); }
}