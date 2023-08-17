#include "GUIInputText.hpp"

namespace Engine
{

void GUIInputText::InnerRender()
{
    if (readOnly)
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));

    ImGui::InputText(m_title.c_str(), m_buffer.data(), m_buffer.size(),
        m_inputTextFlags
            | (hideInput ? ImGuiInputTextFlags_Password : 0)
            | (readOnly ? ImGuiInputTextFlags_ReadOnly : 0)
    );

    if (readOnly)
        ImGui::PopStyleColor();
}

}