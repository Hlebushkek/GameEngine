#pragma once

#include <vector>
#include "Engine.hpp"

class Block : public Engine::IRenderable
{
public:
    Block(uint32_t id, const char* textureFileName, glm::vec3 position);
    Block(uint32_t id, Engine::Texture* texture, glm::vec3 position);

    virtual ~Block();
    void Render(Engine::Shader* shader) override;

    void UpdateMeshSides(int blockFlags);

    uint32_t GetID();
private:
    uint32_t id;

    Engine::Mesh* cubeMesh;
    Engine::Texture* texture;

    void CreateMesh(glm::vec3 position);
};
