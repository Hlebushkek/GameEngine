#include "../include/Mesh.hpp"

namespace Engine
{
    Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices,
        glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;

        this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);
        this->updateModelMatrix();
    }
    Mesh::Mesh(Primitive& primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;

        this->initVAO(primitive);
        this->updateModelMatrix();
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);

        if (this->nrOfIndices > 0)
            glDeleteBuffers(1, &this->EBO);
    }

    //PUBLIC
    void Mesh::Render(Shader* shader)
    {
        this->updateModelMatrix();
        this->updateUniforms(shader);
        
        shader->use();

        glBindVertexArray(this->VAO);
        
        if (this->nrOfIndices == 0)
            glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
        else
            glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

        //Cleanup
        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Mesh::setPosition(const glm::vec3& position)
    {
        this->position = position;
    }
    glm::vec3 Mesh::getPosition()
    {
        return this->position;
    }

    void Mesh::setRotation(const glm::vec3& rotation)
    {
        this->rotation = rotation;
    }

    void Mesh::setScale(const glm::vec3& scale)
    {
        this->scale = scale;
    }

    void Mesh::move(const glm::vec3& position)
    {
        this->position += position;
    }

    void Mesh::rotate(const glm::vec3& rotation)
    {
        this->rotation += rotation;
        
        if (this->rotation.x > 360)
            this->rotation.x -= 360;
        if (this->rotation.y > 360)
            this->rotation.y -= 360;
        if (this->rotation.z > 360)
            this->rotation.z -= 360;
    }

    void Mesh::scaleUp(const glm::vec3& scale)
    {
        this->scale += scale;
    }

    //PRIVATE
    void Mesh::initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
    {
        //Set variables
        this->nrOfVertices = nrOfVertices;
        this->nrOfIndices = nrOfIndices;

        //VAO
        glCreateVertexArrays(1, &this->VAO);
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
    void Mesh::initVAO(Primitive& primitive)
    {
        //Set variables
        this->nrOfVertices = primitive.getNumberOfVertices();
        this->nrOfIndices = primitive.getNumberOfIndices();
        
        //VAO
        glCreateVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);
        //VBO
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), primitive.getVertices(), GL_STATIC_DRAW);
        //EBO
        if (this->nrOfIndices > 0)
        {
            glGenBuffers(1, &this->EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), primitive.getIndices(), GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);
    }

    void Mesh::updateUniforms(Shader* shader)
    {
        shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
    }

    void Mesh::updateModelMatrix()
    {
        this->ModelMatrix = glm::mat4(1.0f);
        this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
        this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
        this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
        this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
        this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
    }
}