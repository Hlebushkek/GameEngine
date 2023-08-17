#pragma once

#include <string>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <glad/glad.h>
#include "GUIObject.hpp"

namespace Engine
{

class ENGINE_API GUIButton : public GUIObject
{

public:
    GUIButton(std::string title, ImVec2 position, ImVec2 size, std::string iconPath = "", const std::function<void()>& onClickCallback = nullptr);
    ~GUIButton();

    void InnerRender() override;

    const ImVec2& GetSize() const { return m_size; }

    void SetOnClick(const std::function<void()>& onClick);

private:
    std::string m_title;
    ImVec2 m_position;
    ImVec2 m_size;
    GLuint m_iconTextureID;
    std::function<void()> m_onClickCallback = nullptr;

};

}