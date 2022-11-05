#include "../include/Application.hpp"
#include "../include/Rect.hpp"
#include "../include/Cube.hpp"

namespace Engine
{
    Application* Application::application = nullptr;

    Application::Application(const char* title, const int width, const int height)
        : WINDOW_WIDTH(width), WINDOW_HEIGHT(height), camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
    {
        this->window = nullptr;
        this->frameBufferWidth = this->WINDOW_WIDTH;
        this->frameBufferHeight = this->WINDOW_HEIGHT;

        this->camPosition = glm::vec3 (0.f, 0.f, 1.f);
        this->worldUp = glm::vec3(0.f, 1.f, 0.f);
        this->camFront = glm::vec3(0.f, 0.f, -1.f);

        this->fov = 90.f;
        this->nearPlane = 0.01f;
        this->farPlane = 1000.f;

        this->deltaTime = 0.f;
        this->curTime = 0.f;
        this->lastTime = 0.f;

        this->InitWindow(title, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        this->InitGLAD();
        this->InitOpenGLOptions();
        this->initMatrices();
        this->InitShaders();
        this->InitTextures();
        this->InitMaterials();
        this->InitLights();

        this->InitUniforms();

        application = this;

        imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
        std::cout << "End App constructor" << std::endl;
    }

    Application::~Application()
    {
        SDL_DestroyWindow(this->window);

        for (size_t i = 0; i < this->shaders.size(); i++)
            delete this->shaders[i];

        for (size_t i = 0; i < this->textures.size(); i++)
            delete this->textures[i];
        
        for (size_t i = 0; i < this->materials.size(); i++)
            delete this->materials[i];

        for (size_t i = 0; i < this->meshes.size(); i++)
            delete this->meshes[i];

        for (size_t i = 0; i < this->lights.size(); i++)
            delete this->lights[i];
    }

    void Application::Run()
    {
        std::cout << "Applicaton satrt Running" << std::endl;
        while(!this->windowShouldClose)
        {
            this->Update();
            // this->Render();
        }
        std::cout << "Applicaton end Running" << std::endl;
    }

    void Application::InitWindow(const char* title, uint32_t windowFlags)
    {
        window = SDL_CreateWindow(title, 400, 400, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);
        assert(this->window);

        SDL_GetWindowSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

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
        this->shaders.push_back(new Shader("resources/vertex_shader.glsl", "resources/fragment_shader.glsl"));
    }

    void Application::InitTextures()
    {
        this->textures.push_back(new Texture("resources/Grass.png", GL_TEXTURE_2D));
        this->textures.push_back(new Texture("resources/Grass_Specular.png", GL_TEXTURE_2D));
        this->textures.push_back(new Texture("resources/WoodLog.png", GL_TEXTURE_2D));
        this->textures.push_back(new Texture("resources/Pavern.png", GL_TEXTURE_2D));
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

    void Application::UpdateUniforms()
    {
        //Update view matrix (camera)
        this->viewMatrix = this->camera.getViewMatrix();

        this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
        this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

        //Update size and projectionMatrix

        SDL_GetWindowSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
        glViewport(0, 0, this->frameBufferWidth, this->frameBufferHeight);

        this->projectionMatrix = glm::mat4(1.f);
        this->projectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
            this->nearPlane, this->farPlane);
        this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
    }

    void Application::UpdateInput()
    {
        while (SDL_PollEvent(&event))
        {
            this->imGuiLayer->OnEvent(event);
            
            this->UpdateMouseInput();

            if (event.type == SDL_KEYDOWN)
            {
                switch (this->event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    SDL_Event event;
                    event.type = SDL_QUIT;
                    SDL_PushEvent(&event);
                    break;
                case SDLK_w:
                    this->camera.move(this->deltaTime, FORWARD);
                    break;
                case SDLK_s:
                    this->camera.move(this->deltaTime, BACKWARD);
                    break;
                case SDLK_a:
                    this->camera.move(this->deltaTime, LEFT);
                    break;
                case SDLK_d:
                    this->camera.move(this->deltaTime, RIGHT);
                    break;
                case SDLK_SPACE:
                    this->camera.move(this->deltaTime, UP);
                    break;
                case SDLK_c:
                    this->camera.move(this->deltaTime, DOWN);
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                // this->updateWheelInput();
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                this->camera.updateMouseMotionInput(deltaTime, this->mouseOffsetX * 50, this->mouseOffsetY * 50);
            }
            else if (event.type == SDL_QUIT)
            {
                this->windowShouldClose = true;
            }
        }
    }

    void Application::UpdateMouseInput()
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        //SDL_GetRelativeMouseState(&mouseOffsetX, &mouseOffsetY);

        this->mouseOffsetX = this->event.motion.xrel;
        this->mouseOffsetY = this->event.motion.yrel;
        // std::cout << mouseOffsetX << " " << mouseOffsetY << std::endl;
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
    }

    void Application::Update()
    {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Update deltaTime
        this->UpdateDeltaTime();

        //Update input
        this->UpdateInput();

        this->UpdateUniforms();

        this->materials[MAT_0]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

        //Use program
        this->shaders[SHADER_CORE_PROGRAM]->use();

        //Activate texture
        this->textures[GRASS]->bind(0);
        this->textures[GRASS_SPECULAR]->bind(1);

        for (Layer* layer : layerStack)
        {
            layer->Update();
            layer->Render(this->shaders[SHADER_CORE_PROGRAM]);
        }

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

    void Application::Render()
    {
        //Clear
        // glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Upate uniforms
        this->UpdateUniforms();

        //Use material
        this->materials[MAT_0]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

        //Use program
        this->shaders[SHADER_CORE_PROGRAM]->use();

        //Activate texture
        this->textures[GRASS]->bind(0);
        this->textures[GRASS_SPECULAR]->bind(1);

        //Render
        this->meshes[MESH_QUAD]->Render(this->shaders[SHADER_CORE_PROGRAM]);

        glFlush();

        SDL_GL_SwapWindow(window);

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Application::UpdateDeltaTime()
    {
        this->curTime = static_cast<float>(SDL_GetTicks()) / 3600.f;
        this->deltaTime = this->curTime - this->lastTime;
        this->lastTime = this->curTime;

        // std::cout << "Delta Time: " << this->deltaTime << std::endl;
    }
}