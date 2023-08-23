#include "GUIButton.hpp"
#include <backends/imgui_impl_opengl3.h>

namespace Engine
{

GUIButton::GUIButton(std::string title, const ImVec2& size, const std::string& iconPath, const std::function<void()>& onClickCallback)
    : GUIObject(), m_title(title), m_position(0, 0), m_size(size), m_iconTextureID(0), m_onClickCallback(onClickCallback)
{
    SDL_Surface* iconSurface = IMG_Load(iconPath.c_str());
    if (!iconSurface)
        return;

    glGenTextures(1, &m_iconTextureID);
    glBindTexture(GL_TEXTURE_2D, m_iconTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iconSurface->w, iconSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, iconSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_DestroySurface(iconSurface);
}

GUIButton::~GUIButton()
{
    if (m_iconTextureID)
        glDeleteTextures(1, &m_iconTextureID);
}

void GUIButton::InnerRender()
{
    ImVec2 cursorPos = ImGui::GetCursorPos();
    if (useCustomPosition)
        cursorPos = m_position;
    
    ImGui::SetCursorPos(cursorPos);
    if (m_iconTextureID)
    {   
        if(ImGui::InvisibleButton(m_title.c_str(), m_size) && enabled)
            if (m_onClickCallback)
                m_onClickCallback();

        ImGui::SetCursorPos(cursorPos);
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(m_iconTextureID)), m_size);
    }
    else
    {   
        if (ImGui::Button(m_title.c_str(), m_size) && enabled)
            if (m_onClickCallback)
                m_onClickCallback();
    }
}

void GUIButton::PreRenderSetup()
{
    if (!enabled)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    }
}

void GUIButton::AfterRenderSetup()
{
    if (!enabled)
    {
        ImGui::PopStyleColor(3);
    }
}

void GUIButton::SetOnClick(const std::function<void()> &onClick)
{
    m_onClickCallback = onClick;
}

}