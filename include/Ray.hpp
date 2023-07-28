#pragma once

#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 origin;
    glm::vec3 end;

    glm::vec3 direction() const { return glm::normalize(end - origin); }
};