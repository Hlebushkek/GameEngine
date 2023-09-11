#pragma once

#include <simd/simd.h>

typedef __attribute__((__ext_vector_type__(3),__aligned__(4))) float simd_packed_float3;

typedef struct MVertex
{
    simd_packed_float3 position;
    simd_packed_float4 color;
    simd_packed_float2 texture_coord;
    simd_packed_float3 normal;
} MVertex;

typedef struct __attribute__ ((__packed__)) MVertexGeneric
{
    simd_packed_float4 color;
    simd_packed_float2 texcoord;
    simd_packed_float3 normal;
} MVertexGeneric;

typedef struct MFrameData
{
    simd::float4x4 view_matrix;
    simd::float4x4 projection_matrix;
    simd_packed_float3 camera_position;
    unsigned int framebuffer_width;
    unsigned int framebuffer_height;
} MFrameData;

typedef struct MMeshData
{
    simd::float4x4 model_matrix;
    bool is_texture_bound;
} MMeshData;

typedef struct MMaterial
{
    simd_packed_float3 ambient;
    simd_packed_float3 diffuse;
    simd_packed_float3 specular;
} MMaterial;

typedef struct MLight
{
    simd_packed_float3 ambient;
    simd_packed_float3 diffuse;
    simd_packed_float3 specular;
} MLight;

typedef enum MBufferIndex
{
    MBufferIndexMeshPositions     = 0,
    MBufferIndexMeshGenerics      = 1,
    MBufferIndexFrameData         = 2,
    MBufferIndexMeshData          = 3,
    MBufferIndexMaterialData      = 4,
    MBufferIndexLightsPosition    = 5,
    MBufferIndexLightsData        = 6,
} MBufferIndex;

typedef enum MVertexAttributes
{
    MVertexAttributePosition  = 0,
    MVertexAttributeColor     = 1,
    MVertexAttributeTexcoord  = 2,
    MVertexAttributeNormal    = 3,
} MVertexAttributes;

typedef enum MTextureIndex
{
	MTextureIndexBaseColor = 0,
	MTextureIndexSpecular  = 1,
	MTextureIndexNormal    = 2,
    MTextureIndexShadow    = 3,
    MTextureIndexAlpha     = 4,

    MNumMeshTextures = MTextureIndexNormal + 1
} MTextureIndex;