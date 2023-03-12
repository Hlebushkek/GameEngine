#include "../include/Shader.hpp"

namespace Engine
{
    Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
    {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

        if (strlen(geometryFile) != 0)
            geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

        fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

        this->linkProgram(vertexShader, geometryShader, fragmentShader);
        
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
    }
    Shader::~Shader()
    {
        glDeleteProgram(this->id);
    }

    //Public methods
    void Shader::use()
    {
        glUseProgram(this->id);
    }

    void Shader::unuse()
    {
        glUseProgram(0);
    }

    void Shader::set1i(GLint value, const GLchar* name)
    {
        this->use();

        glUniform1i(glGetUniformLocation(this->id, name), value);

        this->unuse();
    }

    void Shader::setVec1f(GLfloat value, const GLchar* name)
    {
        this->use();

        glUniform1f(glGetUniformLocation(this->id, name), value);

        this->unuse();
    }

    void Shader::setVec2f(glm::fvec2 value, const GLchar* name)
    {
        this->use();

        glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void Shader::setVec3f(glm::fvec3 value, const GLchar* name)
    {
        this->use();

        glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void Shader::setVec4f(glm::fvec4 value, const GLchar* name)
    {
        this->use();

        glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose)
    {
        this->use();

        glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

        this->unuse();
    }

    void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
    {
        this->use();

        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

        this->unuse();
    }

    //Private methods
    std::string Shader::loadShaderSource(const char* fileName)
    {
        char* presfix = "../../Sandbox/resources/";
        char* full_path = (char*)malloc(strlen(presfix)+strlen(fileName)+1); 
        strcpy(full_path, presfix); 
        strcat(full_path, fileName);

        std::string temp = "";
        std::string src = "";

        std::ifstream in_file;
        in_file.open(full_path);

        if (in_file.is_open())
        {
            while(std::getline(in_file, temp))
            {
                src += temp + "\n";
            }
        } else { std::cout << "ERROR::SHADER::SHADER::COULD_NOT_OPEN_FILE: " << fileName << std::endl; }

        in_file.close();

        return src;
    }

    GLuint Shader::loadShader(GLenum type, const char* fileName)
    {
        char infoLog[512];
        GLint success;

        GLuint shader = glCreateShader(type);

        std::string str_src = this->loadShaderSource(fileName);
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

    void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
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
}