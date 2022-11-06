#include "../include/ChunkRenderer.hpp"
#include "../include/Block.hpp"

ChunkRenderer::ChunkRenderer(glm::uvec3 chunkSize)
    : CHUNK_SIZE(chunkSize)
{
    textures.emplace_back(new Engine::Texture("Grass.png", GL_TEXTURE_2D));

    InitBlocksArray();
}

ChunkRenderer::~ChunkRenderer()
{
    for (size_t i = 0; i < CHUNK_SIZE.x; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE.y; j++)
        {
            for (size_t k = 0; k < CHUNK_SIZE.z; k++)
            {
                delete this->blocks[i][j][k];
            }
            delete this->blocks[i][j];
        }
        delete this->blocks[i];
    }
}

void ChunkRenderer::InitBlocksArray()
{
    this->blocks = new Block***[CHUNK_SIZE.x];

    for (size_t i = 0; i < CHUNK_SIZE.x; i++)
    {
        blocks[i] = new Block**[CHUNK_SIZE.y];
 
        for (size_t j = 0; j < CHUNK_SIZE.y; j++)
        {
            blocks[i][j] = new Block*[CHUNK_SIZE.z];
            for (size_t k = 0; k < CHUNK_SIZE.z; k++)
            {
                this->blocks[i][j][k] = new Block(0, textures[0], glm::vec3(0.0625f * i, 0.0625f * j, 0.0625f * k));
            }
        }
    }

    for (size_t i = 0; i < CHUNK_SIZE.x; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE.y; j++)
        {
            for (size_t k = 0; k < CHUNK_SIZE.z; k++)
            {
                BlockWasPlacedAt(glm::uvec3(i, j, k));
            }
        }
    }
}

bool ChunkRenderer::IsBlockFilled(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE.x || y >= CHUNK_SIZE.y || z >= CHUNK_SIZE.z) return false;

    if (blocks[x][y][z]) return true;
    else return false;
}

bool ChunkRenderer::IsBlockFilled(glm::uvec3 pos)
{
    return this->IsBlockFilled(pos.x, pos.y, pos.z);
}

void ChunkRenderer::BlockWasDestroyedAt(glm::uvec3 pos)
{

}

void ChunkRenderer::BlockWasPlacedAt(glm::uvec3 pos)
{
    UpdateNearbyBlocksFor(pos);
}

void ChunkRenderer::UpdateNearbyBlocksFor(glm::uvec3 pos)
{
    UpdateBlockAt(pos.x + 1, pos.y, pos.z);
    if (pos.x > 0) UpdateBlockAt(pos.x - 1, pos.y, pos.z);
    
    UpdateBlockAt(pos.x, pos.y + 1, pos.z);
    if (pos.y > 0) UpdateBlockAt(pos.x, pos.y - 1, pos.z);

    UpdateBlockAt(pos.x, pos.y, pos.z + 1);
    if (pos.z > 0) UpdateBlockAt(pos.x, pos.y, pos.z - 1);
}

void ChunkRenderer::UpdateBlockAt(int x, int y, int z)
{
    if (!IsBlockFilled(x, y, z)) return;

    int blockFlags = 0;

    if (IsBlockFilled(x + 1, y, z)) blockFlags |= LEFT;
    if (IsBlockFilled(x - 1, y, z)) blockFlags |= RIGHT;

    if (IsBlockFilled(x, y + 1, z)) blockFlags |= UP;
    if (IsBlockFilled(x, y - 1, z)) blockFlags |= DOWN;

    if (IsBlockFilled(x, y, z + 1)) blockFlags |= FORWARD;
    if (IsBlockFilled(x, y, z - 1)) blockFlags |= BACKWARD;

    if (blocks[x][y][z])
        blocks[x][y][z]->UpdateMeshSides(blockFlags);
}

void ChunkRenderer::UpdateBlockAt(glm::uvec3 pos)
{
    this->UpdateBlockAt(pos.x, pos.y, pos.z);
}