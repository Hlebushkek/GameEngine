#pragma once
#include <Engine.hpp>
#include "Enums.hpp"

class ChunkRenderer
{
public:
	ChunkRenderer(glm::uvec3 chunkSize);
	virtual ~ChunkRenderer() = default;

    bool IsBlockFilled(int x, int y, int z);
    bool IsBlockFilled(glm::uvec3 pos);

    void BlockWasDestroyedAt(glm::uvec3 pos);
    void BlockWasPlacedAt(glm::uvec3 pos);

    void UpdateBlockAt(int x, int y, int z);
    void UpdateBlockAt(glm::uvec3 pos);

    Engine::Mesh**** meshArray;
private:
    const glm::uvec3 CHUNK_SIZE;

    void InitCubeArray();
    void FillChunk();

    void UpdateNearbyBlocksFor(glm::uvec3 pos);
};