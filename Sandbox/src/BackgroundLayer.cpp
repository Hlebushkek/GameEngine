#include "../include/BackgroundLayer.hpp"
#include "../include/SandBox.hpp"

BackgroundLayer::BackgroundLayer() : Layer("BackgroundLayer") {}

void BackgroundLayer::OnAttach()
{
    
}

void BackgroundLayer::OnDetach()
{

}

void BackgroundLayer::Update()
{

}

void BackgroundLayer::OnImGuiRender() 
{
    ImGui::SetCurrentContext(SandBox::Get()->imguiContext);
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
	ImGui::End();
}