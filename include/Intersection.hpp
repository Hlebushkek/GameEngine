#pragma once

#include <glm/glm.hpp>

namespace Engine
{

class GameObject;

struct Intersection
{
    glm::vec3 point;
    GameObject *object;
};

}