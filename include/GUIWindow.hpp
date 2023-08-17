#pragma once

#include <string>
#include <vector>
#include "GUIObject.hpp"

namespace Engine
{

class GUIView;

class ENGINE_API GUIWindow : public GUIObject
{
public:
    GUIWindow(std::string title, bool isOpen = true, ImGuiWindowFlags windowFlags = 0)
        : GUIObject(), m_title(title), m_windowFlags(windowFlags) { this->isVisible = isOpen; }

    void Render() override;
    void InnerRender() override;

protected:
    std::string m_title;
    ImGuiWindowFlags m_windowFlags;

    std::vector<GUIView*> m_subviews;

};

}