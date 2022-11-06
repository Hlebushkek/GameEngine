#pragma once

#include <vector>

#include <Engine.hpp>
#include "Enums.hpp"

class Block;

class ChunkRenderer
{
public:
	ChunkRenderer(glm::uvec3 chunkSize);
	virtual ~ChunkRenderer();

    bool IsBlockFilled(int x, int y, int z);
    bool IsBlockFilled(glm::uvec3 pos);

    void BlockWasDestroyedAt(glm::uvec3 pos);
    void BlockWasPlacedAt(glm::uvec3 pos);

    void UpdateBlockAt(int x, int y, int z);
    void UpdateBlockAt(glm::uvec3 pos);

    Block**** blocks;
private:
    const glm::uvec3 CHUNK_SIZE;

    std::vector<Engine::Texture*> textures;

    void InitBlocksArray();

    void UpdateNearbyBlocksFor(glm::uvec3 pos);
};