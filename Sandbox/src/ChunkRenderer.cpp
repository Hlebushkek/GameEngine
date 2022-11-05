#include "../include/ChunkRenderer.hpp"

ChunkRenderer::ChunkRenderer(glm::uvec3 chunkSize)
    : CHUNK_SIZE(chunkSize)
{
    InitCubeArray();
    FillChunk();
}

void ChunkRenderer::InitCubeArray()
{
    this->meshArray = new Engine::Mesh***[CHUNK_SIZE.x];
 
    for (size_t i = 0; i < CHUNK_SIZE.x; i++)
    {
        meshArray[i] = new Engine::Mesh**[CHUNK_SIZE.y];
 
        for (size_t j = 0; j < CHUNK_SIZE.y; j++)
        {
            meshArray[i][j] = new Engine::Mesh*[CHUNK_SIZE.z];
        }
    }
}

void ChunkRenderer::FillChunk()
{
    for (size_t i = 0; i < CHUNK_SIZE.x; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE.y; j++)
        {
            for (size_t k = 0; k < CHUNK_SIZE.z; k++)
            {
                Engine::Primitive cube = Engine::Cube();
                this->meshArray[i][j][k] = new Engine::Mesh(cube, glm::vec3(0.0625f * i, 0.0625f * j, 0.0625f * k), glm::vec3(0.f), glm::vec3(0.0625f));
                BlockWasPlacedAt(glm::uvec3(i, j, k));
            }
        }
    }
    UpdateBlockAt(glm::uvec3(CHUNK_SIZE.x-1, CHUNK_SIZE.y-1, CHUNK_SIZE.z-1));
}

bool ChunkRenderer::IsBlockFilled(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE.x || y >= CHUNK_SIZE.y || z >= CHUNK_SIZE.z) return false;

    if (meshArray[x][y][z]) return true;
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
    if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE.x || y >= CHUNK_SIZE.y || z >= CHUNK_SIZE.z) return;

    int blockFlags = 0;

    if (IsBlockFilled(x + 1, y, z)) blockFlags |= LEFT;
    if (IsBlockFilled(x - 1, y, z)) blockFlags |= RIGHT;

    if (IsBlockFilled(x, y + 1, z)) blockFlags |= UP;
    if (IsBlockFilled(x, y - 1, z)) blockFlags |= DOWN;

    if (IsBlockFilled(x, y, z + 1)) blockFlags |= FORWARD;
    if (IsBlockFilled(x, y, z - 1)) blockFlags |= BACKWARD;

    Engine::Primitive cube = Engine::Cube(blockFlags);

    if (!meshArray[x][y][z]) delete meshArray[x][y][z];
    meshArray[x][y][z] = new Engine::Mesh(cube, glm::vec3(0.0625f * x, 0.0625f * y, 0.0625f * z), glm::vec3(0.f), glm::vec3(0.0625f));
}

void ChunkRenderer::UpdateBlockAt(glm::uvec3 pos)
{
    this->UpdateBlockAt(pos.x, pos.y, pos.z);
}