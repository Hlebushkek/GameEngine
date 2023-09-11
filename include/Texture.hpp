#pragma once

#include <iostream>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <glad/glad.h>
#include "Core.hpp"

#ifdef __APPLE__
namespace std {
    template <>
    struct hash<std::filesystem::path> {
        size_t operator()(const std::filesystem::path& p) const {
            return std::hash<std::string>{}(p.string());
        }
    };
}
#endif

struct SDL_Surface;

namespace Engine
{

class ENGINE_API Texture
{
public:
    ~Texture();

    void Bind(const int texture_unit);
    void Unbind();

    static Texture* LoadTexture(const std::string& fileName);

private:
    Texture(SDL_Surface* surface);
    static std::unordered_map<std::filesystem::path, Texture*> texturesMap;

private:
    class Impl;
    std::unique_ptr<Impl> impl;

};

}
