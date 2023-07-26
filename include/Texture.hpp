#pragma once

#include <iostream>
#include <filesystem>
#include <unordered_map>

#include <glad/glad.h>

#include "Core.hpp"

namespace Engine
{
    class ENGINE_API Texture
    {
    public:
        ~Texture();

        inline GLuint getID() const { return this->id; }

        void bind(const GLint texture_unit);
        void unbind(GLenum type);

        static Texture *LoadTexture(const std::string &fileName, GLenum type);

    private:
        Texture(GLint id, GLenum type, int width, int height);
        static std::unordered_map<std::filesystem::path, Texture*> texturesMap;

        GLuint id;
        GLenum type;

        int width;
        int height;

    };
}