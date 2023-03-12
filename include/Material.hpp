#pragma once

#include <iostream>
#include "Shader.hpp"

namespace Engine
{
    class Material
    {
    public:
        Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
        ~Material() {}

        void sendToShader(Shader& program);

    private:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        GLint diffuseTex;
        GLint specularTex;
    };
}