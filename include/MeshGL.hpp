#pragma once

#include <iostream>
#include <vector>

#include "Core.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Primitive.hpp"
#include "ShaderTypesCommon.h"

typedef unsigned int GLuint;

namespace Engine
{

class ENGINE_API Mesh
{
public:
    Mesh(Primitive& primitive);
    Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);
    ~Mesh();

    void Render(Shader* shader, const MeshData& data);

private:
    void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);

private:
    unsigned nrOfVertices;
    unsigned nrOfIndices;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

};

}