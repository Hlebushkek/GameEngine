#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core.hpp"

struct FrameData;
struct MeshData;
struct Material;

#ifdef ENABLE_METAL
namespace MTL { class Device; }
#endif

namespace Engine
{

class Texture;
struct Light;

class ENGINE_API Shader
{
public:
#ifdef ENABLE_METAL
    Shader(const char* file);
#else
    Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");
#endif
    ~Shader();

    void Use();
    void Unuse();

    void SetFrameData(const FrameData& data);
    void SetMeshData(const MeshData& data);
    void SetMaterial(const Material& material);
    void SetLights(const std::vector<Light*>& lights);
    void SetTexture(Texture* texture, int index);

private:
    class Impl;
    std::unique_ptr<Impl> impl;

};

}