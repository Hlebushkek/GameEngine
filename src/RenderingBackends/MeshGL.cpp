#include <glad/glad.h>
#include "MeshGL.hpp"
#include "Shader.hpp"

namespace Engine
{

Mesh::Mesh(Primitive& primitive)
    : Mesh(primitive.getVertices(), primitive.getNumberOfVertices(), primitive.getIndices(), primitive.getNumberOfIndices()) {}

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
{
    this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);

    if (this->nrOfIndices > 0)
        glDeleteBuffers(1, &this->EBO);
}

void Mesh::Render(Shader* shader, const MeshData& data)
{
    shader->SetMeshData(data);
    shader->Use();

    glBindVertexArray(this->VAO);
    
    if (this->nrOfIndices == 0)
        glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
    else
        glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    shader->Unuse();
}

void Mesh::initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
{
    //Set variables
    this->nrOfVertices = nrOfVertices;
    this->nrOfIndices = nrOfIndices;

    //VAO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    //VBO
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
    //EBO
    if (this->nrOfIndices > 0)
    {
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
    }

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

}