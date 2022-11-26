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

    bool RayCast::GetObjects()
    {
        Engine::Application* app = Application::Get();
        
        glm::vec4 mousePos = glm::vec4(app->GetMousePosition() - glm::vec3(app->GetWidth() / 2, app->GetHeight() / 2, 0.f), 1.f);
        glm::mat4 viewMatrix = app->GetViewMatrix();
        
        glm::vec4 rayVector = viewMatrix * mousePos;

        // std::cout << "Mat: " << glm::to_string(viewMatrix) << std::endl;
        // std::cout << "MousePos: " << mousePos.x << " " << mousePos.y << " " << mousePos.z << std::endl;
        std::cout << "RayVector: " << rayVector.x << " " << rayVector.y << " " << rayVector.z << std::endl;
        return false;
    }
}