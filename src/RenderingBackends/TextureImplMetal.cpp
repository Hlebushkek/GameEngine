#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <SDL3/SDL.h>
#include "TextureImplMetal.hpp"
#include "Renderer.hpp"
#include "RenderingContext.hpp"

namespace Engine
{

Texture::Impl::Impl(SDL_Surface* surface) : width(surface->w), height(surface->h)
{
    MTL::Device* device = Renderer::GetRenderingContext()->device;

    MTL::TextureDescriptor* textureDesc = MTL::TextureDescriptor::alloc()->init();
    textureDesc->setWidth(width);
    textureDesc->setHeight(height);
    textureDesc->setPixelFormat(MTL::PixelFormatRGBA8Unorm);//here
    textureDesc->setTextureType(MTL::TextureType2D);
    textureDesc->setStorageMode(MTL::StorageModeManaged);
    textureDesc->setUsage(MTL::ResourceUsageSample | MTL::ResourceUsageRead);

    m_texture = device->newTexture(textureDesc);
    m_texture->replaceRegion(MTL::Region(0, 0, 0, width, height, 1 ), 0, surface->pixels, width * 4);

    textureDesc->release();
}

Texture::Impl::~Impl()
{
    m_texture->release();
}

void Texture::Impl::Bind(const int texture_unit)
{
    Renderer::GetRenderingContext()->renderEncoder->setFragmentTexture(m_texture, texture_unit);
}

void Texture::Impl::Unbind()
{

}

}