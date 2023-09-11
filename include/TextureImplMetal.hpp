#pragma once

#include "Texture.hpp"

namespace MTL { class Texture; }

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
    MTL::Texture* m_texture;
    int width, height;

};

}