#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#ifdef ENABLE_METAL
#include "TextureImplMetal.hpp"
#else
#include "TextureImplGL.hpp"
#endif
#include "Texture.hpp"
#include "config.h"

namespace Engine
{

std::unordered_map<std::filesystem::path, Texture*> Texture::texturesMap = {};

Texture::Texture(SDL_Surface* surface) : impl(std::make_unique<Impl>(surface)) {}
Texture::~Texture()
{

}

void Texture::Bind(const int texture_unit)
{
    impl->Bind(texture_unit);
}

void Texture::Unbind()
{
    impl->Unbind();
}

Texture *Texture::LoadTexture(const std::string& fileName)
{
    if (texturesMap.find(fileName) != texturesMap.end())
        return texturesMap[fileName];
    
    Texture* texture;
    std::string full_path = RESOURCES_DIR + fileName;

    SDL_Surface* textureImage = IMG_Load(full_path.c_str());
    if (!textureImage)
    {
        std::cout << "ERROR::TEXTURE::LOAD_FROM_FILE::TEXTURE_LOADING_FAILED " << full_path << std::endl;
        return nullptr;
    }

    SDL_Surface* rgbSurface = SDL_ConvertSurfaceFormat(textureImage, SDL_PIXELFORMAT_RGBA32);

    texture = new Texture(rgbSurface);
    texturesMap.insert(std::make_pair(fileName, texture));

    SDL_DestroySurface(textureImage);
    SDL_DestroySurface(rgbSurface);

    return texture;
}

}
