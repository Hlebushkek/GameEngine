#include "UIObject.hpp"

namespace Engine
{
    UIObject::UIObject(const char* fileName, Primitive& primitive, glm::vec2 position, glm::vec3 rotation, glm::vec2 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;

        this->InitVAO(primitive);

        this->texture = new Texture(fileName, GL_TEXTURE_2D);
    }

    UIObject::~UIObject()
    {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);

        if (this->nrOfIndices > 0)
            glDeleteBuffers(1, &this->EBO);

        delete this->texture;
        delete this->primitive;
    }

    void UIObject::InitVAO(Primitive& primitive)
    {
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

    void UIObject::Render(Shader* shader)
    {
        this->UpdateModelMatrix();
        this->UpdateUniforms(shader);

        shader->use();

        texture->bind(0);

        glBindVertexArray(this->VAO);
        
        if (this->nrOfIndices == 0)
            glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
        else
            glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

        texture->unbind(0);

        //Cleanup
        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void UIObject::UpdateModelMatrix()
    {
        this->modelMatrix = glm::mat4(1.0f);
        this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(this->position.x, this->position.y, 0));
        this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
        this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
        this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
        this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(this->scale.x, this->scale.y, 1));
    }
    
    void UIObject::UpdateUniforms(Shader* shader)
    {
        shader->setMat4fv(this->modelMatrix, "ModelMatrix");
    }
}