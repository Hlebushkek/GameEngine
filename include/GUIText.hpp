#pragma once

#include <string>
#include "GUIObject.hpp"

namespace Engine
{

class ENGINE_API GUIText : public GUIObject
{
public:
    GUIText(const std::string& text = "");

    void SetText(const std::string& text) { this->m_text = text; }
    void SetCustomPosition(const ImVec2& position) { useCustomPosition = true; this->m_position = position; }

    void InnerRender() override;

public:
    bool useCustomPosition = false;

private:
    std::string m_text;
    ImVec2 m_position;

};

}