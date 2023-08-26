#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "Core.hpp"

namespace Engine
{
    class ENGINE_API Shader
    {
    public:
        Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");
        ~Shader();

        void use();
        void unuse();

        void set1i(GLint value, const GLchar* name);
        void set1f(GLfloat value, const GLchar* name);

        void setVec1f(GLfloat value, const GLchar* name);
        void setVec2f(glm::fvec2 value, const GLchar* name);
        void setVec3f(glm::fvec3 value, const GLchar* name);
        void setVec4f(glm::fvec4 value, const GLchar* name);

        void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
        void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
    private:
        //Private member variables
        GLuint id;

        //Private Func
        std::string loadShaderSource(const std::string& fileName);
        GLuint loadShader(GLenum type, const std::string& fileName);

        void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);

    };
}
