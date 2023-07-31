#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <imgui.h>
#include <glad/glad.h>
#include "Core.hpp"
#include <iostream>
#include <functional>

namespace Engine
{

class ENGINE_API Button
{

public:
    Button(const std::string& name, const ImVec2& position, const ImVec2& size, const std::string& iconPath, const std::function<void()>& onClickCallback = nullptr);
    ~Button();

    void Render();

    const ImVec2& GetSize() const { return size; }

    // void SetOnClick(const std::function<void()>& onClick);

private:
    std::string name;
    ImVec2 position;
    ImVec2 size;
    GLuint iconTextureID;
    std::function<void()> onClickCallback = nullptr;

};

}