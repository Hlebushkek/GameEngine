#pragma once

#include <iostream>
#include <vector>

#include "Core.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Primitive.hpp"

namespace Engine
{
    class ENGINE_API Mesh
    {
    public:
        Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);
        Mesh(Primitive& primitive);
        ~Mesh();

        void update();
        void Render(Shader* shader);

    private:
        unsigned nrOfVertices;
        unsigned nrOfIndices;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);
        void initVAO(Primitive& primitive);
    };
}