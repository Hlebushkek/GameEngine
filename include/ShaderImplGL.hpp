#pragma once

#include "Shader.hpp"

namespace Engine
{

class Shader::Impl
{
public:
    Impl(const char* vertexFile, const char* fragmentFile, const char* geometryFile);
    ~Impl();

    void Use();
    void Unuse();

    void SetFrameData(const FrameData& data);
    void SetMeshData(const MeshData& data);
    void SetMaterial(const Material& mat);
    void SetLights(const std::vector<Light*>& lights);
    void SetTexture(Texture* tex, int index);

    void Set1i(int value, const char* name);
    void Set1f(float value, const char* name);

    void SetVec1f(float value, const char* name);
    void SetVec2f(glm::fvec2 value, const char* name);
    void SetVec3f(glm::fvec3 value, const char* name);
    void SetVec4f(glm::fvec4 value, const char* name);

    void SetMat3fv(glm::mat3 value, const char* name, bool transpose = false);
    void SetMat4fv(glm::mat4 value, const char* name, bool transpose = false);
    
private:
    std::string LoadShaderSource(const std::string& fileName);
    unsigned LoadShader(unsigned type, const std::string& fileName);
    void LinkProgram(unsigned vertexShader, unsigned fragmentShader, unsigned geometryShader);

private:
    unsigned id;

};

}