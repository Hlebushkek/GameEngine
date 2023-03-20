#pragma once

#include <iostream>
#include <cstring>

#include <glad/glad.h>

#include "Core.hpp"

namespace Engine
{
    class ENGINE_API Texture
    {
    public:
        Texture(const char* fileName, GLenum type);
        ~Texture();

        inline GLuint getID() const { return this->id; }

        void bind(const GLint texture_unit);
        void unbind(GLenum type);

        void loadTexture(const char* fileName);

    private:
        GLuint id;
        int width;
        int height;
        GLenum type;

    };
}