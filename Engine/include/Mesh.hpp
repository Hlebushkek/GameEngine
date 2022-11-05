#pragma once

#include <iostream>
#include <vector>

#include "Core.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Primitive.hpp"
#include "IRenderable.hpp"

namespace Engine
{
    class ENGINE_API Mesh : public IRenderable
    {
    public:
        Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices,
            glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
        Mesh(Primitive& primitive, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
        ~Mesh();

        void update();
        void Render(Shader* shader) override;

        void setPosition(const glm::vec3& position);
        void setRotation(const glm::vec3& rotation);
        void setScale(const glm::vec3& scale);

        void move(const glm::vec3& position);
        void rotate(const glm::vec3& rotation);
        void scaleUp(const glm::vec3& scale);

    private:
        unsigned nrOfVertices;
        unsigned nrOfIndices;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 ModelMatrix;

        void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);
        void initVAO(Primitive& primitive);
        void initModelMatrix();

        void updateUniforms(Shader* shader);

        void updateModelMatrix();
    };
}