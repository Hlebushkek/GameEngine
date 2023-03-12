#include "../include/RayCast.hpp"
#include "../include/Application.hpp"
#include "../include/Layer.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace Engine
{
    RayCast::RayCast()
    {

    }

    glm::vec4 RayCast::GetVectorForMouse()
    {
        Engine::Application* app = Application::Get();
        
        glm::vec3 sdlMousePos = app->GetMousePosition();
        glm::vec4 mousePos = glm::vec4(sdlMousePos.x - app->GetWidth() / 2, app->GetHeight() / 2 - sdlMousePos.y, 1.f, 1.f);

        glm::mat4 viewMatrix = app->GetViewMatrix();
        glm::vec4 rayVector = viewMatrix * mousePos;

        std::cout << "RayVector: " << glm::to_string(rayVector) << std::endl;
        return rayVector;
    }
}