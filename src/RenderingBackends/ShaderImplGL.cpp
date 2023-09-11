#include <glad/glad.h>
#include "ShaderImplGL.hpp"
#include "ShaderTypesCommon.h"
#include "Lights.hpp"
#include "config.h"

namespace Engine
{

Shader::Impl::Impl(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
    GLuint vertexShader = 0;
    GLuint geometryShader = 0;
    GLuint fragmentShader = 0;

    vertexShader = LoadShader(GL_VERTEX_SHADER, vertexFile);

    if (strlen(geometryFile) != 0)
        geometryShader = LoadShader(GL_GEOMETRY_SHADER, geometryFile);

    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentFile);

    LinkProgram(vertexShader, geometryShader, fragmentShader);
    
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
}

Shader::Impl::~Impl()
{
    glDeleteProgram(this->id);
}

void Shader::Impl::Use()
{
    glUseProgram(this->id);
}

void Shader::Impl::Unuse()
{
    glUseProgram(0);
}

void Shader::Impl::SetFrameData(const FrameData& data)
{
    glViewport(0, 0, data.framebuffer_width, data.framebuffer_height);

    SetMat4fv(data.view_matrix, "ViewMatrix");
    SetMat4fv(data.projection_matrix, "ProjectionMatrix");
    SetVec3f(data.camera_position, "cameraPos");
}

void Shader::Impl::SetMeshData(const MeshData& data)
{
    SetMat4fv(data.model_matrix, "ModelMatrix");
    Set1i(data.is_texture_bound, "isTextureBound");
}

void Shader::Impl::SetMaterial(const Material &mat)
{
    SetVec3f(mat.ambient, "material.ambient");
    SetVec3f(mat.diffuse, "material.diffuse");
    SetVec3f(mat.specular, "material.specular");

    Set1i(0, "material.diffuseTex");
    Set1i(1, "material.specularTex");
}

void Shader::Impl::SetLights(const std::vector<Light*> &lights)
{
    for (size_t i = 0; i < lights.size(); i++)
    {
        std::string uniformNameBase = "lights[" + std::to_string(i) + "].";
        Set1i(static_cast<int>(lights[i]->GetType()), (uniformNameBase + "type").c_str());
    
        SetVec3f(lights[i]->ambient, (uniformNameBase + "ambient").c_str());
        SetVec3f(lights[i]->diffuse, (uniformNameBase + "diffuse").c_str());
        SetVec3f(lights[i]->specular, (uniformNameBase + "specular").c_str());

        if (auto pointLight = dynamic_cast<PointLight*>(lights[i]))
        {
            SetVec3f(pointLight->position, (uniformNameBase + "position").c_str());

            Set1f(pointLight->constant, (uniformNameBase + "constant").c_str());
            Set1f(pointLight->linear, (uniformNameBase + "linear").c_str());
            Set1f(pointLight->quadratic, (uniformNameBase + "quadratic").c_str());
        }
        else if (auto directionLight = dynamic_cast<DirectionalLight*>(lights[i]))
        {
            SetVec3f(directionLight->direction, (uniformNameBase + "direction").c_str());
        }
        else if (auto spotLight = dynamic_cast<SpotLight*>(lights[i]))
        {
            SetVec3f(spotLight->position, (uniformNameBase + "position").c_str());
            SetVec3f(spotLight->direction, (uniformNameBase + "direction").c_str());
        
            Set1f(spotLight->constant, (uniformNameBase + "constant").c_str());
            Set1f(spotLight->linear, (uniformNameBase + "linear").c_str());
            Set1f(spotLight->quadratic, (uniformNameBase + "quadratic").c_str());

            Set1f(spotLight->cutOff, (uniformNameBase + "cutOff").c_str());
            Set1f(spotLight->outerCutOff, (uniformNameBase + "outerCutOff").c_str());
        }
    }

    for (size_t i = lights.size(); i < 20; i++)
    {
        std::string uniformName = "lights[" + std::to_string(i) + "].";
        Set1i(0, (uniformName  + "type").c_str());
    }
}

void Shader::Impl::SetTexture(Texture *tex, int index)
{

}

void Shader::Impl::Set1i(int value, const char* name)
{
    this->Use();

    glUniform1i(glGetUniformLocation(this->id, name), value);

    this->Unuse();
}

void Shader::Impl::Set1f(float value, const char* name)
{
    this->Use();

    glUniform1f(glGetUniformLocation(this->id, name), value);

    this->Unuse();
}

void Shader::Impl::SetVec1f(float value, const char* name)
{
    this->Use();

    glUniform1f(glGetUniformLocation(this->id, name), value);

    this->Unuse();
}

void Shader::Impl::SetVec2f(glm::fvec2 value, const char* name)
{
    this->Use();

    glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    this->Unuse();
}

void Shader::Impl::SetVec3f(glm::fvec3 value, const char* name)
{
    this->Use();

    glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    this->Unuse();
}

void Shader::Impl::SetVec4f(glm::fvec4 value, const char* name)
{
    this->Use();

    glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    this->Unuse();
}

void Shader::Impl::SetMat3fv(glm::mat3 value, const char* name, bool transpose)
{
    this->Use();

    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

    this->Unuse();
}

void Shader::Impl::SetMat4fv(glm::mat4 value, const char* name, bool transpose)
{
    this->Use();

    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

    this->Unuse();
}

void Shader::Impl::LinkProgram(unsigned vertexShader, unsigned fragmentShader, unsigned geometryShader)
{
    char infoLog[512];
    GLint success;
    
    this->id = glCreateProgram();

    glAttachShader(this->id, vertexShader);

    if (geometryShader)
        glAttachShader(this->id, geometryShader);

    glAttachShader(this->id, fragmentShader);

    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glUseProgram(0);
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

GLuint Shader::Impl::LoadShader(unsigned type, const std::string& fileName)
{
    char infoLog[512];
    GLint success;

    GLuint shader = glCreateShader(type);

    std::string str_src = this->LoadShaderSource(fileName);
    const GLchar* src = str_src.c_str();

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << std::endl;
        std::cout << infoLog << std::endl;
    }

    return shader;
}

}