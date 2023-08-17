#include "GUIView.hpp"

namespace Engine
{

void GUIView::Render()
{
    if (m_visible && ImGui::BeginChild(m_title.c_str(), m_size, m_border))
    {
        for (auto view : m_subviews)
            view->Render();

        ImGui::EndChild();
    }
}

}