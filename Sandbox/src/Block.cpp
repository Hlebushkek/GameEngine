#include "../include/Block.hpp"

Block::Block(uint32_t id, const char* textureFileName, glm::vec3 position)
{
    this->id = id;
    this->texture = new Engine::Texture(textureFileName, GL_TEXTURE_2D);

    CreateMesh(position);
}

Block::Block(uint32_t id, Engine::Texture* texture, glm::vec3 position)
{
    this->id = id;
    this->texture = texture;

    CreateMesh(position);
}

Block::~Block()
{
    // delete texture;
}

uint32_t Block::GetID()
{
    return this->id;
}

void Block::CreateMesh(glm::vec3 position)
{
    Engine::Primitive cube = Engine::Cube();
    this->cubeMesh = new Engine::Mesh(cube, position, glm::vec3(0.f), glm::vec3(0.0625f));
}

void Block::UpdateMeshSides(int blockFlags)
{
    glm::vec3 blockPos = this->cubeMesh->getPosition();

    if (this->cubeMesh)
        delete this->cubeMesh;

    Engine::Primitive cube = Engine::Cube(blockFlags);
    this->cubeMesh = new Engine::Mesh(cube, blockPos, glm::vec3(0.f), glm::vec3(0.0625f));
}

void Block::Render(Engine::Shader* shader)
{
    texture->bind(0);
    cubeMesh->Render(shader);
    texture->unbind(0);
}