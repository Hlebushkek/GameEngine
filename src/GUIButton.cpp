#include "GUIButton.hpp"
#include <backends/imgui_impl_opengl3.h>

namespace Engine
{

GUIButton::GUIButton(std::string title, ImVec2 position, ImVec2 size, std::string iconPath, const std::function<void()>& onClickCallback)
    : GUIObject(), m_title(title), m_position(position), m_size(size), m_iconTextureID(0), m_onClickCallback(onClickCallback)
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
    ImGui::SetCursorPos(m_position);
    if (m_iconTextureID)
    {   
        if(ImGui::InvisibleButton(m_title.c_str(), m_size))
            if (m_onClickCallback)
                m_onClickCallback();

        ImGui::SetCursorPos(m_position);
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(m_iconTextureID)), m_size);
    }
    else
    {   
        if (ImGui::Button(m_title.c_str(), m_size))
            if (m_onClickCallback)
                m_onClickCallback();
    }
}

void GUIButton::SetOnClick(const std::function<void()> &onClick)
{
    m_onClickCallback = onClick;
}

}