#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Texture.hpp"
#include "config.h"

namespace Engine
{
    std::unordered_map<std::filesystem::path, Texture*> Texture::texturesMap = {};

    Texture::Texture(GLint id, GLenum type, int width, int height) : id(id), type(type), width(width), height(height) {}
    Texture::~Texture() { glDeleteTextures(1, &this->id); }

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

    Texture *Texture::LoadTexture(const std::string& fileName, GLenum type)
    {
        if (texturesMap.find(fileName) != texturesMap.end())
            return texturesMap[fileName];
        
        Texture *texture;
        std::string full_path = RESOURCES_DIR + fileName;

        SDL_Surface *textureImage = IMG_Load(full_path.c_str());
        if (!textureImage)
        {
            std::cout << "ERROR::TEXTURE::LOAD_FROM_FILE::TEXTURE_LOADING_FAILED " << full_path << std::endl;
            return nullptr;
        }

        SDL_Surface* rgbSurface = SDL_ConvertSurfaceFormat(textureImage, SDL_PIXELFORMAT_RGBA32);

        int width = rgbSurface->w;
        int height = rgbSurface->h;

        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(type, id);

        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLenum imgFormat = rgbSurface->format->Amask == 0 ? GL_RGB : GL_RGBA;  
        glTexImage2D(type, 0, imgFormat, width, height, 0, imgFormat, GL_UNSIGNED_BYTE, rgbSurface->pixels);
        glGenerateMipmap(type);

        texture = new Texture(id, type, width, height);
        texturesMap.insert(std::make_pair(fileName, texture));

        glActiveTexture(0);
        glBindTexture(type, 0);
        SDL_DestroySurface(textureImage);
        SDL_DestroySurface(rgbSurface);

        return texture;
    }
}
