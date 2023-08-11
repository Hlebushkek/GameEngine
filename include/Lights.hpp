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

class ENGINE_API Light
{
public:
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular) {}

    virtual ~Light() = default;

    virtual void SendToShader(Shader& program, int index) = 0;
    virtual LightType GetType() { return LightType::None; }

protected:
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;

};

class ENGINE_API PointLight : public Light
{
public:
    PointLight(glm::vec3 position = glm::vec3(0.f),
               glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f),
               float constant = 0.8f, float linear = 0.09f, float quadratic = 0.032f)
        : Light(ambient, diffuse, specular), m_Position(position), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic) {}

    void SendToShader(Shader& program, int index) override
    {
        std::string uniformName = "lights[" + std::to_string(index) + "].";
        program.set1i(static_cast<int>(GetType()), (uniformName + "type").c_str());

        program.setVec3f(m_Position, (uniformName + "position").c_str());
    
        program.setVec3f(m_Ambient, (uniformName + "ambient").c_str());
        program.setVec3f(m_Diffuse, (uniformName + "diffuse").c_str());
        program.setVec3f(m_Specular, (uniformName + "specular").c_str());
    
        program.set1f(m_Constant, (uniformName + "constant").c_str());
        program.set1f(m_Linear, (uniformName + "linear").c_str());
        program.set1f(m_Quadratic, (uniformName + "quadratic").c_str());
    }

    LightType GetType() override { return LightType::Point; }

private:
    glm::vec3 m_Position;

    float m_Constant;
    float m_Linear;
    float m_Quadratic;

};

class ENGINE_API DirectionalLight : public Light
{
public:
    DirectionalLight(glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f),
                     glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f))
        : Light(ambient, diffuse, specular), m_Direction(direction) {}

    void SendToShader(Shader& program, int index) override
    {
        std::string uniformName = "lights[" + std::to_string(index) + "].";
        program.set1i(static_cast<int>(GetType()), (uniformName + "type").c_str());

        program.setVec3f(m_Direction, (uniformName + "direction").c_str());
    
        program.setVec3f(m_Ambient, (uniformName + "ambient").c_str());
        program.setVec3f(m_Diffuse, (uniformName + "diffuse").c_str());
        program.setVec3f(m_Specular, (uniformName + "specular").c_str());
    }

    LightType GetType() override { return LightType::Directional; }

private:
    glm::vec3 m_Direction;

};

class ENGINE_API SpotLight : public Light
{
public:
    SpotLight(glm::vec3 position = glm::vec3(0.f), glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f),
              glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f),
              float constant = 0.8f, float linear = 0.09f, float quadratic = 0.032f,
              float cutOff = glm::cos(glm::radians(12.5f)), float outerCutOff = glm::cos(glm::radians(75.0f)))
        : Light(ambient, diffuse, specular), m_Position(position), m_Direction(direction),
                m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic),
                m_CutOff(cutOff), m_OuterCutOff(outerCutOff) {}

    void SendToShader(Shader& program, int index) override
    {
        std::string uniformName = "lights[" + std::to_string(index) + "].";
        program.set1i(static_cast<int>(GetType()), (uniformName + "type").c_str());

        program.setVec3f(m_Position, (uniformName + "position").c_str());
        program.setVec3f(m_Direction, (uniformName + "direction").c_str());
    
        program.setVec3f(m_Ambient, (uniformName + "ambient").c_str());
        program.setVec3f(m_Diffuse, (uniformName + "diffuse").c_str());
        program.setVec3f(m_Specular, (uniformName + "specular").c_str());
    
        program.set1f(m_Constant, (uniformName + "constant").c_str());
        program.set1f(m_Linear, (uniformName + "linear").c_str());
        program.set1f(m_Quadratic, (uniformName + "quadratic").c_str());

        program.set1f(m_CutOff, (uniformName + "cutOff").c_str());
        program.set1f(m_OuterCutOff, (uniformName + "outerCutOff").c_str());
    }

    LightType GetType() override { return LightType::Spot; }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Direction;

    float m_Constant;
    float m_Linear;
    float m_Quadratic;

    float m_CutOff;
    float m_OuterCutOff;

};

}