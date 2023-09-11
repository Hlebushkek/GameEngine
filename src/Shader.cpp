#ifdef ENABLE_METAL
#include "ShaderImplMetal.hpp"
#else
#include "ShaderImplGL.hpp"
#endif
#include "Shader.hpp"
#include "Lights.hpp"

namespace Engine
{

#ifdef ENABLE_METAL
    Shader::Shader(const char* file) : impl(std::make_unique<Impl>(file))
#else
    Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile) 
    : impl(std::make_unique<Impl>(vertexFile, fragmentFile, geometryFile))
#endif
    {}

Shader::~Shader() {}

void Shader::Use()
{
    impl->Use();
}

void Shader::Unuse()
{
    impl->Unuse();
}

void Shader::SetFrameData(const FrameData& data)
{
    impl->SetFrameData(data);
}

void Shader::SetMeshData(const MeshData& data)
{
    impl->SetMeshData(data);
}

void Shader::SetMaterial(const Material& material)
{
    impl->SetMaterial(material);
}

void Shader::SetLights(const std::vector<Light*>& lights)
{
    impl->SetLights(lights);
}

void Shader::SetTexture(Texture* texture, int index)
{
    impl->SetTexture(texture, index);
}

}
