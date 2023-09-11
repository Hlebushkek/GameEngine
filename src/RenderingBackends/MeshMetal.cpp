#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include "MeshMetal.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "RenderingContext.hpp"
#include "ShaderTypesMetal.h"

namespace Engine
{

Mesh::Mesh(Primitive& primitive)
    : Mesh(primitive.getVertices(), primitive.getNumberOfVertices(), primitive.getIndices(), primitive.getNumberOfIndices()) {}

Mesh::Mesh(Vertex* vertices, const unsigned& nrOfVertices, unsigned* indices, const unsigned& nrOfIndices)
{
    MTL::Device* device = Renderer::GetRenderingContext()->device;

    int positionElementSize = sizeof(simd_packed_float3);
    int positionDataSize    = positionElementSize * nrOfVertices;

    int genericElementSize = sizeof(MVertexGeneric);
    int genericsDataSize   = genericElementSize * nrOfVertices;

    int indexElementSize = sizeof(unsigned);
    int indicesDataSize = nrOfIndices ? indexElementSize * nrOfIndices : indexElementSize * nrOfVertices;

    m_verticesPositionBuffer = device->newBuffer(positionDataSize, MTL::ResourceStorageModeManaged);
    m_verticesGenericBuffer = device->newBuffer(genericsDataSize, MTL::ResourceStorageModeManaged);
    m_meshDataBuffer = device->newBuffer(sizeof(MMeshData), MTL::ResourceStorageModeManaged);
    m_indicesBuffer = device->newBuffer(indicesDataSize, MTL::ResourceStorageModeManaged);

    simd_packed_float3* positionsArray = (simd_packed_float3*)m_verticesPositionBuffer->contents();
    MVertexGeneric* genericsArray = (MVertexGeneric*)m_verticesGenericBuffer->contents();

    for(unsigned long vertex = 0; vertex < nrOfVertices; vertex++)
    {
        positionsArray[vertex].x = vertices[vertex].position.x;
        positionsArray[vertex].y = vertices[vertex].position.y;
        positionsArray[vertex].z = vertices[vertex].position.z;
        genericsArray[vertex].color[0] = vertices[vertex].color.r;
        genericsArray[vertex].color[1] = vertices[vertex].color.g;
        genericsArray[vertex].color[2] = vertices[vertex].color.b;
        genericsArray[vertex].color[3] = vertices[vertex].color.a;
        genericsArray[vertex].texcoord[0] = vertices[vertex].texcoord.x;
        genericsArray[vertex].texcoord[1] = vertices[vertex].texcoord.y;
        genericsArray[vertex].normal[0] = vertices[vertex].normal.x;
        genericsArray[vertex].normal[1] = vertices[vertex].normal.y;
        genericsArray[vertex].normal[2] = vertices[vertex].normal.z;
    }
    
    if (nrOfIndices)
        memcpy(m_indicesBuffer->contents(), indices, nrOfIndices * sizeof(uint32_t));
    else
    {
        unsigned* indicesBufferContent = (unsigned*)m_indicesBuffer->contents();
        for (size_t i = 0; i < nrOfVertices; i++)
            indicesBufferContent[i] = (unsigned)i;
    }

    m_verticesPositionBuffer->didModifyRange(NS::Range::Make(0, m_verticesPositionBuffer->length()));
    m_verticesGenericBuffer->didModifyRange(NS::Range::Make(0, m_verticesGenericBuffer->length()));
    m_indicesBuffer->didModifyRange(NS::Range::Make(0, m_indicesBuffer->length()));
}

Mesh::~Mesh()
{
    m_verticesPositionBuffer->release();
    m_verticesGenericBuffer->release();
    m_meshDataBuffer->release();
    m_indicesBuffer->release();
}

void Mesh::Render(Shader* shader, const MeshData& data)
{
    shader->Use();

    memcpy(m_meshDataBuffer->contents(), &data, sizeof(MMeshData));

    auto ctx = Renderer::GetRenderingContext();
    ctx->renderEncoder->setVertexBuffer(m_verticesPositionBuffer, 0, MBufferIndexMeshPositions);
    ctx->renderEncoder->setVertexBuffer(m_verticesGenericBuffer, 0, MBufferIndexMeshGenerics);
    ctx->renderEncoder->setVertexBuffer(m_meshDataBuffer, 0, MBufferIndexMeshData);
    ctx->renderEncoder->setCullMode(MTL::CullModeBack);
    ctx->renderEncoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);
    unsigned long indicesSize = m_indicesBuffer->length() / sizeof(uint32_t);
    ctx->renderEncoder->drawIndexedPrimitives(
        MTL::PrimitiveTypeTriangle, indicesSize, MTL::IndexTypeUInt32,
        m_indicesBuffer, 0);
}

}
