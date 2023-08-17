#include "GUIView.hpp"
#include "GUIWindow.hpp"

namespace Engine
{

void GUIWindow::InnerRender()
{
    for (auto view : m_subviews)
        view->Render();
}

void GUIWindow::Render()
{
    if (!isVisible) return;
    this->PreRenderSetup();
    
    if (ImGui::Begin(m_title.c_str(), &isVisible, m_windowFlags))
        this->InnerRender();
    ImGui::End();
}

}