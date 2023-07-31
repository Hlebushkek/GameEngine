#pragma once

#include <glm/glm.hpp>
#include "Core.hpp"

namespace Engine
{

class GameObject;

struct ENGINE_API Intersection
{
    glm::vec3 point;
    GameObject *object;
};

}