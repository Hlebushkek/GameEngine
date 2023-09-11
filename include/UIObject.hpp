#pragma once

#include "Core.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Primitive.hpp"

namespace Engine
{
    class ENGINE_API UIObject
    {
    public:
        UIObject(const char* fileName, Primitive& primitive, glm::vec2 position, glm::vec3 rotation, glm::vec2 scale);
        virtual ~UIObject();

        void Render(Shader* shader);
    private:
        unsigned nrOfVertices;
        unsigned nrOfIndices;

        unsigned VAO;
        unsigned VBO;
        unsigned EBO;

        glm::vec2 position;
        glm::vec3 rotation;
        glm::vec2 scale;

        glm::mat4 modelMatrix;

        Primitive* primitive;
        Texture* texture;

        void InitVAO(Primitive& primitive);
        void UpdateUniforms(Shader* shader);
        void UpdateModelMatrix();
    };
}