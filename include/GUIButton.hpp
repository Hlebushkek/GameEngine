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
    GUIButton(std::string title, const ImVec2& size = ImVec2(0, 0), const std::string& iconPath = "", const std::function<void()>& onClickCallback = nullptr);
    ~GUIButton();

    void InnerRender() override;
    void PreRenderSetup() override;
    void AfterRenderSetup() override;

    const ImVec2& GetSize() const { return m_size; }

    void SetCustomPosition(const ImVec2& position) { useCustomPosition = true; this->m_position = position; }
    void SetOnClick(const std::function<void()>& onClick);

public:
    bool useCustomPosition = false;
    bool enabled = true;

private:
    std::string m_title;
    ImVec2 m_position;
    ImVec2 m_size;
    GLuint m_iconTextureID;
    std::function<void()> m_onClickCallback = nullptr;

};

}