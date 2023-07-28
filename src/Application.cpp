#include "Application.hpp"
#include "Ray.hpp"
#include "Rect.hpp"
#include "Cube.hpp"

namespace Engine
{
    Application* Application::application = nullptr;

    Application::Application(const char* title, const int width, const int height)
        : WINDOW_WIDTH(width), WINDOW_HEIGHT(height), camera(glm::vec3(0.f, 0.f, 1.f))
    {
        this->window = nullptr;
        this->frameBufferWidth = this->WINDOW_WIDTH;
        this->frameBufferHeight = this->WINDOW_HEIGHT;

        this->camPosition = glm::vec3(0.f, 0.f, 1.f);
        this->worldUp = glm::vec3(0.f, 1.f, 0.f);
        this->camFront = glm::vec3(0.f, 0.f, -1.f);

        this->fov = 90.f;
        this->nearPlane = 0.01f;
        this->farPlane = 1000.f;

        this->InitWindow(title, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        this->InitGLAD();
        this->InitOpenGLOptions();
        this->initMatrices();
        this->InitShaders();
        this->InitMaterials();
        this->InitLights();
        this->InitUniforms();

        application = this;

        inputHandler = InputHandler::Get();

        imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
        std::cout << "End App constructor" << std::endl;
    }

    Application::~Application()
    {        
        SDL_DestroyWindow(this->window);

        for (size_t i = 0; i < this->shaders.size(); i++)
            delete this->shaders[i];
        
        for (size_t i = 0; i < this->materials.size(); i++)
            delete this->materials[i];

        for (size_t i = 0; i < this->meshes.size(); i++)
            delete this->meshes[i];

        for (size_t i = 0; i < this->lights.size(); i++)
            delete this->lights[i];
    }

    void Application::Run()
    {
        while(!this->windowShouldClose)
            this->Update();
    }

    void Application::InitWindow(const char* title, uint32_t windowFlags)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        window = SDL_CreateWindow(title, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);
        assert(this->window);

        SDL_GetWindowSizeInPixels(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

        this->glContext = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, glContext);
        // SDL_ShowCursor(SDL_DISABLE);
        // SDL_SetRelativeMouseMode(SDL_TRUE);

        SDL_PumpEvents();
        // SDL_GetMouseState(&lastMouseX, &lastMouseY);
        // SDL_GetMouseState(&mouseX, &mouseY);
    }

    void Application::InitGLAD()
    {
        int status = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
        assert(status);
    }

    void Application::InitOpenGLOptions()
    {
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void Application::initMatrices()
    {
        this->viewMatrix = glm::mat4(1.f);
        this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

        this->projectionMatrix = glm::mat4(1.f);
        this->projectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
            this->nearPlane, this->farPlane);
    }

    void Application::InitShaders()
    {
        this->shaders.push_back(new Shader("vertex_shader.glsl", "fragment_shader.glsl"));
        this->shaders.push_back(new Shader("ui_vertex_shader.glsl", "fragment_shader.glsl"));
    }

    void Application::InitMaterials()
    {
        this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
            0, 1));
    }

    void Application::InitLights()
    {
        this->lights.push_back(new glm::vec3(0.f, 0.f, 1.0f));
    }

    void Application::InitUniforms()
    {
        Shader* core_program = this->shaders[SHADER_CORE_PROGRAM];
        core_program->setMat4fv(this->viewMatrix, "ViewMatrix");
        core_program->setMat4fv(this->projectionMatrix, "ProjectionMatrix");

        core_program->setVec3f(*this->lights[0], "lightPos0");

        Shader* ui_program = this->shaders[SHADER_UI_PROGRAM];
        ui_program->setVec3f(*this->lights[0], "lightPos0");
    }

    void Application::CastRay()
    {
        glm::vec3 sdlMousePos = inputHandler->GetMousePosition();

        float ndcX = (2.0f * sdlMousePos.x) / frameBufferWidth - 1.0f;
        float ndcY = 1.0f - (2.0f * sdlMousePos.y) / frameBufferHeight;

        glm::mat4 viewMatrix = GetViewMatrix();

        glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);
        glm::mat4 inverseProjectionMatrix = glm::inverse(projectionMatrix);

        glm::vec4 rayStartNDC(ndcX, ndcY, -1.0, 1.0);
        glm::vec4 rayEndNDC(ndcX, ndcY, 0.0, 1.0);

        glm::vec4 rayStartWorld = inverseProjectionMatrix * rayStartNDC;
        glm::vec4 rayEndWorld = inverseProjectionMatrix * rayEndNDC;

        rayStartWorld /= rayStartWorld.w;
        rayEndWorld /= rayEndWorld.w;

        Ray mouseRay { glm::vec3(rayStartWorld), glm::vec3(rayEndWorld) };
        for (auto layer : layerStack)
            layer->CheckCollisions(mouseRay);
    }

    void Application::PushLayer(Layer* layer)
    {
        layerStack.PushLayer(layer);
		layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        layerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Update()
    {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->UpdateDeltaTime();
        this->HandlEvents();
        this->UpdateUniforms();
        this->CastRay();

        this->materials[MAT_0]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
        this->materials[MAT_0]->sendToShader(*this->shaders[SHADER_UI_PROGRAM]);

        camera.Update();

        for (Layer* layer : layerStack)
        {
            layer->Update();
            layer->Render(this->shaders[SHADER_CORE_PROGRAM]);
        }

        for (Layer* layer : layerStack)
            layer->RenderUI(this->shaders[SHADER_UI_PROGRAM]);

        imGuiLayer->Begin();
        {
            for (Layer* layer : layerStack)
                layer->OnImGuiRender();
        }
        imGuiLayer->End();
        
        glFlush();

        SDL_GL_SwapWindow(window);

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Application::HandlEvents()
    {
        this->inputHandler->Reset();
        
        while (SDL_PollEvent(&event))
        {
            this->imGuiLayer->OnEvent(event);
            this->inputHandler->HandleInput(event);

            if (event.type == SDL_EVENT_QUIT)
                this->windowShouldClose = true;
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
            SDL_SetRelativeMouseMode((SDL_bool)this->windowGrab);
        }
    }

    void Application::UpdateDeltaTime()
    {
        Uint64 ticks = SDL_GetTicks();
        this->curTime = static_cast<float>(ticks) / 1000.;
        this->deltaTime = this->curTime - this->lastTime;
        this->lastTime = this->curTime;

        // std::cout << "Ticks: " << ticks << std::endl;
        // std::cout << "Delta Time: " << this->deltaTime << std::endl;
    }

    void Application::UpdateUniforms()
    {
        //Update view matrix (camera)
        this->viewMatrix = this->camera.getViewMatrix();

        this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
        this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.transform().GetPosition(), "cameraPos");

        //Update size and projectionMatrix
        SDL_GetWindowSizeInPixels(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
        glViewport(0, 0, this->frameBufferWidth, this->frameBufferHeight);

        this->projectionMatrix = glm::mat4(1.f);
        this->projectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
            this->nearPlane, this->farPlane);
        this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
    }
    
    glm::mat4 Application::GetViewMatrix()
    {
        return this->camera.getViewMatrix();
    }
}