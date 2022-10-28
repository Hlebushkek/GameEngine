#include <SDL2/SDL.h>
#include "../include/Texture.hpp"

namespace Engine
{
    Texture::Texture(const char* fileName, GLenum type)
    {
        this->type = type;

        loadTexture(fileName);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &this->id);
    }

    void Texture::bind(const GLint texture_unit)
    {
        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glBindTexture(this->type, this->id);
    }

    void Texture::unbind(GLenum type)
    {
        glActiveTexture(0);
        glBindTexture(this->type, 0);
    }

    void Texture::loadTexture(const char* fileName)
    {
        if (this->id)
        {
            glDeleteTextures(1, &this->id);
        }
        std::cout << "Before IMG_LOAD" << std::endl;
        SDL_Surface *textureImage = IMG_Load(fileName);
        std::cout << "After IMG_LOAD" << std::endl;
        if (textureImage)
        {
            this->width = textureImage->w;
            this->height = textureImage->h;

            GLenum imgFormat = GL_RGB;
            if (textureImage->format->Amask != 0)
            {
                imgFormat = GL_RGBA;
            }

            glGenTextures(1, &this->id);
            glBindTexture(this->type, this->id);

            glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glTexImage2D(this->type, 0, imgFormat, this->width, this->height, 0, imgFormat, GL_UNSIGNED_BYTE, textureImage->pixels);
            glGenerateMipmap(this->type);
        } else { std::cout << "ERROR::TEXTURE::LOAD_FROM_FILE::TEXTURE_LOADING_FAILED" << fileName << std::endl; }

        glActiveTexture(0);
        glBindTexture(this->type, 0);
        SDL_FreeSurface(textureImage);
        std::cout << "AFTER FREE SURFACE " << fileName << std::endl;
    }
}