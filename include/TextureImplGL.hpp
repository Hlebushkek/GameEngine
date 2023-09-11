#pragma once

#include "Texture.hpp"

namespace Engine
{

class Texture::Impl
{
public:
    Impl(SDL_Surface* surface);
    ~Impl();

    void Bind(const int texture_unit);
    void Unbind();

private:
    int width, height;

    unsigned id;
    unsigned type;

};

}