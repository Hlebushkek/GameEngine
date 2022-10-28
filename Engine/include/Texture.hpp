#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <SDL_image.h>

namespace Engine
{
    class Texture
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