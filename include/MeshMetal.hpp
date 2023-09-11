#pragma once

#include <iostream>
#include <vector>
#include "Primitive.hpp"
#include "Core.hpp"
#include "ShaderTypesCommon.h"

namespace MTL { class Buffer; class Device; }

namespace Engine
{

class Shader;

class ENGINE_API Mesh
{
public:
    Mesh(Primitive& primitive);
    Mesh(Vertex* vertices, const unsigned& nrOfVertices, unsigned* indices, const unsigned& nrOfIndices);
    ~Mesh();

    void Render(Shader* shader, const MeshData& data);

private:
    MTL::Buffer* m_verticesPositionBuffer;
    MTL::Buffer* m_verticesGenericBuffer;
    MTL::Buffer* m_meshDataBuffer;
    MTL::Buffer* m_indicesBuffer;

};

}
