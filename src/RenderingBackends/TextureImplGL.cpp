#include <glad/glad.h>
#include <SDL3/SDL.h>
#include "TextureImplGL.hpp"

namespace Engine
{

Texture::Impl::Impl(SDL_Surface* surface) : type(GL_TEXTURE_2D)
{
    glGenTextures(1, &id);
    glBindTexture(type, id);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum imgFormat = surface->format->Amask == 0 ? GL_RGB : GL_RGBA;
    width = surface->w;
    height = surface->h;

    glTexImage2D(type, 0, imgFormat, width, height, 0, imgFormat, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(type);

    glActiveTexture(0);
    glBindTexture(type, 0);
}

Texture::Impl::~Impl()
{
    glDeleteTextures(1, &this->id);
}

void Texture::Impl::Bind(const int texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(this->type, this->id);
}

void Texture::Impl::Unbind()
{
    glActiveTexture(0);
    glBindTexture(this->type, 0);
}

}