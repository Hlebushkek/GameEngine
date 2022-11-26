#pragma once

#include <glm/glm.hpp>
#include "Core.hpp"

namespace Engine
{
    class ENGINE_API BoxCollider
    {
    public:
        BoxCollider(glm::vec3 size, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1),
            glm::vec3 positionOffset = glm::vec3(0));
        virtual ~BoxCollider() = default;
    private:
        
        glm::vec3 size;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::vec3 positionOffset;
    };
}