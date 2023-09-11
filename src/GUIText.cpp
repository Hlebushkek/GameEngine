#include "GUIText.hpp"


namespace Engine
{

GUIText::GUIText(const std::string &text) : m_text(text) {}

void GUIText::InnerRender()
{
    ImVec2 cursorPos = ImGui::GetCursorPos();
    if (useCustomPosition)
        cursorPos = m_position;
    
    ImGui::SetCursorPos(cursorPos);
    ImGui::Text("%s", m_text.c_str());
}

}