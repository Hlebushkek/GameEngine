#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include "Texture.hpp"
#include "Renderer.hpp"
#include "RenderingContext.hpp"
#include "ShaderImplMetal.hpp"
#include "ShaderTypesMetal.h"
#include "ShaderTypesCommon.h"
#include "config.h"

namespace Engine
{

Shader::Impl::Impl(const char* file)
{
    MTL::Device* device = Renderer::GetRenderingContext()->device;

    InitBuffers(device);
    InitVertexDescriptor();

    NS::Error* error = nullptr;
    std::string shaderSrc = LoadShaderSource(file);
    MTL::Library* library = device->newLibrary(NS::String::string(shaderSrc.c_str(), NS::UTF8StringEncoding), nullptr, &error);
    if (!library)
    {
        __builtin_printf("%s", error->localizedDescription()->utf8String());
        assert(false);
    }

    MTL::Function* vertexFn = library->newFunction(NS::String::string("vertexMain", NS::UTF8StringEncoding));
    MTL::Function* fragFn = library->newFunction(NS::String::string("fragmentMain", NS::UTF8StringEncoding));

    MTL::RenderPipelineDescriptor* renderPipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    renderPipelineDescriptor->setLabel(NS::String::string("G-buffer Creation", NS::UTF8StringEncoding));
    renderPipelineDescriptor->setVertexDescriptor(m_defaultVertexDescriptor);
    renderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

    renderPipelineDescriptor->setVertexFunction(vertexFn);
    renderPipelineDescriptor->setFragmentFunction(fragFn);

    m_renderPipelineState = device->newRenderPipelineState(renderPipelineDescriptor, &error);
    if (!m_renderPipelineState)
    {
        __builtin_printf("%s", error->localizedDescription()->utf8String());
        assert(false);
    }

    vertexFn->release();
    fragFn->release();
    renderPipelineDescriptor->release();
    library->release();
}

Shader::Impl::~Impl()
{
    m_defaultVertexDescriptor->release();
    m_renderPipelineState->release();
}

void Shader::Impl::Use()
{
    auto renderEncoder = Renderer::GetRenderingContext()->renderEncoder;
    renderEncoder->setRenderPipelineState(m_renderPipelineState);
    renderEncoder->setVertexBuffer(m_frameDataBuffer, 0, MBufferIndexFrameData);
    renderEncoder->setVertexBuffer(m_meshDataBuffer , 0, MBufferIndexMeshData);
    renderEncoder->setVertexBuffer(m_materialBuffer , 0, MBufferIndexMaterialData);
}

void Shader::Impl::Unuse()
{

}

std::string Shader::Impl::LoadShaderSource(const std::string &fileName)
{
    std::string full_path = RESOURCES_DIR + fileName;

    std::string temp = "";
    std::string src = "";

    std::ifstream in_file;
    in_file.open(full_path);

    if (in_file.is_open())
        while(std::getline(in_file, temp))
            src += temp + "\n";
    else std::cout << "ERROR::SHADER::SHADER::COULD_NOT_OPEN_FILE: " << fileName << std::endl;

    in_file.close();

    return src;
}

void Shader::Impl::SetFrameData(const FrameData& data)
{
    memcpy(m_frameDataBuffer->contents(), &data, sizeof(MFrameData));
}

void Shader::Impl::SetMeshData(const MeshData& data)
{
    
}

void Shader::Impl::SetMaterial(const Material& mat)
{
    memcpy(m_materialBuffer->contents(), &mat, sizeof(MMaterial));
}

void Shader::Impl::SetLights(const std::vector<Light*> &lights)
{
    
}

void Shader::Impl::SetTexture(Texture* tex, int index)
{

}

void Shader::Impl::InitVertexDescriptor()
{
    m_defaultVertexDescriptor = MTL::VertexDescriptor::alloc()->init();

    // Positions.
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributePosition)->setFormat(MTL::VertexFormatFloat3);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributePosition)->setOffset(0);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributePosition)->setBufferIndex(MBufferIndexMeshPositions);

    // Color.
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeColor)->setFormat(MTL::VertexFormatFloat4);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeColor)->setOffset(0);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeColor)->setBufferIndex(MBufferIndexMeshGenerics);

    // Texture coordinates.
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeTexcoord)->setFormat(MTL::VertexFormatFloat2);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeTexcoord)->setOffset(16);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeTexcoord)->setBufferIndex(MBufferIndexMeshGenerics);

    // Normals.
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeNormal)->setFormat(MTL::VertexFormatFloat3);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeNormal)->setOffset(24);
    m_defaultVertexDescriptor->attributes()->object(MVertexAttributeNormal)->setBufferIndex(MBufferIndexMeshGenerics);

    // Position Buffer Layout
    m_defaultVertexDescriptor->layouts()->object(MBufferIndexMeshPositions)->setStride(16);
    m_defaultVertexDescriptor->layouts()->object(MBufferIndexMeshPositions)->setStepRate(1);
    m_defaultVertexDescriptor->layouts()->object(MBufferIndexMeshPositions)->setStepFunction(MTL::VertexStepFunctionPerVertex);

    // Generic Attribute Buffer Layout
    m_defaultVertexDescriptor->layouts()->object(MBufferIndexMeshGenerics)->setStride(40);
    m_defaultVertexDescriptor->layouts()->object(MBufferIndexMeshGenerics)->setStepRate(1);
    m_defaultVertexDescriptor->layouts()->object(MBufferIndexMeshGenerics)->setStepFunction(MTL::VertexStepFunctionPerVertex);
}

void Shader::Impl::InitBuffers(MTL::Device* device)
{
    m_frameDataBuffer = device->newBuffer(sizeof(MFrameData), MTL::ResourceStorageModeManaged);
    m_meshDataBuffer = device->newBuffer(sizeof(MMeshData), MTL::ResourceStorageModeManaged);
    m_materialBuffer = device->newBuffer(sizeof(MMaterial), MTL::ResourceStorageModeManaged);
    m_lightBuffer = device->newBuffer(sizeof(MLight), MTL::ResourceStorageModeManaged);
}

}
