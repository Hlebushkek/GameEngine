#pragma once

#include "Shader.hpp"

namespace MTL { class Device; class RenderPipelineState; class VertexDescriptor; class Buffer; class Device; }

namespace Engine
{

class Shader::Impl
{
public:
    Impl(const char* file);
    ~Impl();

    void Use();
    void Unuse();

    void SetFrameData(const FrameData& data);
    void SetMeshData(const MeshData& data);
    void SetMaterial(const Material& mat);
    void SetLights(const std::vector<Light*>& lights);
    void SetTexture(Texture* tex, int index);
    
private:
    void InitVertexDescriptor();
    void InitBuffers(MTL::Device* device);
    std::string LoadShaderSource(const std::string& fileName);

private:
    MTL::VertexDescriptor* m_defaultVertexDescriptor;
    MTL::RenderPipelineState* m_renderPipelineState;

    MTL::Buffer* m_frameDataBuffer;
    MTL::Buffer* m_meshDataBuffer;
    MTL::Buffer* m_materialBuffer;
    MTL::Buffer* m_lightBuffer;

};

}