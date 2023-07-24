#pragma once

#include <iostream>
#include <array>
#include <vector>

#include "Core.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

namespace Engine
{

class ENGINE_API GameObject
{
public:
    GameObject(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));

    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition();
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);

    void move(const glm::vec3& position);
    void rotate(const glm::vec3& rotation);
    void scaleUp(const glm::vec3& scale);
    
    void virtual Render(Shader* shader);

    static const glm::vec3 WORLD_FRONT; // Todo: move it to some kind of world settings class
    static const glm::vec3 WORLD_UP; // Todo: move it to some kind of world settings class

    //Virtual
    virtual void Update() {}

protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    glm::mat4 ModelMatrix;

    std::vector<Mesh*> meshes;
    
    void updateUniforms(Shader* shader);
    void updateDirections();
    void updateModelMatrix();
};

}
