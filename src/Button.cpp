#include "Button.hpp"
#include <backends/imgui_impl_opengl3.h>

namespace Engine
{

Button::Button(const std::string& name, const ImVec2& position, const ImVec2& size, const std::string& iconPath, const std::function<void()>& onClickCallback)
    : name(name), position(position), size(size), iconTextureID(0), onClickCallback(onClickCallback)
{
    SDL_Surface* iconSurface = IMG_Load(iconPath.c_str());
    if (!iconSurface)
        return;

    glGenTextures(1, &iconTextureID);
    glBindTexture(GL_TEXTURE_2D, iconTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iconSurface->w, iconSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, iconSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_DestroySurface(iconSurface);
}

Button::~Button()
{
    if (iconTextureID)
    {
        glDeleteTextures(1, &iconTextureID);
        iconTextureID = 0;
    }
}

void Button::Render()
{
    ImGui::SetCursorPos(position);
    if (iconTextureID)
    {   
        if(ImGui::InvisibleButton(name.c_str(), size))
            if (onClickCallback)
                onClickCallback();

        ImGui::SetCursorPos(position);
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(iconTextureID)), size);
    }
    else
    {   
        if (ImGui::Button(name.c_str(), size))
            if (onClickCallback)
                onClickCallback();
    }
}

}