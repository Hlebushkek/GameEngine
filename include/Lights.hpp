#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

namespace Engine
{

enum class LightType
{
    None = 0,
    Point,
    Directional,
    Spot
};

struct ENGINE_API Light
{
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {}

    virtual LightType GetType() { return LightType::None; }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

};

struct ENGINE_API PointLight : public Light
{
    PointLight(glm::vec3 position = glm::vec3(0.f),
               glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f),
               float constant = 0.8f, float linear = 0.09f, float quadratic = 0.032f)
        : Light(ambient, diffuse, specular), position(position), constant(constant), linear(linear), quadratic(quadratic) {}

    LightType GetType() override { return LightType::Point; }

    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

};

struct ENGINE_API DirectionalLight : public Light
{
    DirectionalLight(glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f),
                     glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f))
        : Light(ambient, diffuse, specular), direction(direction) {}

    LightType GetType() override { return LightType::Directional; }

    glm::vec3 direction;

};

struct ENGINE_API SpotLight : public Light
{
    SpotLight(glm::vec3 position = glm::vec3(0.f), glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f),
              glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f),
              float constant = 0.8f, float linear = 0.09f, float quadratic = 0.032f,
              float cutOff = glm::cos(glm::radians(12.5f)), float outerCutOff = glm::cos(glm::radians(75.0f)))
        : Light(ambient, diffuse, specular), position(position), direction(direction),
                constant(constant), linear(linear), quadratic(quadratic),
                cutOff(cutOff), outerCutOff(outerCutOff) {}

    LightType GetType() override { return LightType::Spot; }

    glm::vec3 position;
    glm::vec3 direction;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

};

}