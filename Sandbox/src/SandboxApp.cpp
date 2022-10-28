#include <Engine.hpp>
#include <include/EntryPoint.hpp>
#include "../include/SandBox.hpp"
#include "../include/BackgroundLayer.hpp"
#include "../include/InterfaceLayer.hpp"


SandBox::SandBox(const char* title, const int width, const int height)
    : Engine::Application(title, width, height)
{
    BackgroundLayer* backgroundLayer = new BackgroundLayer();
    PushLayer(backgroundLayer);

    InterfaceLayer* interfaceLayer = new InterfaceLayer();
    PushLayer(interfaceLayer);
}

Engine::Application* Engine::CreateApplication()
{
    return new SandBox("MineEngine", 600, 400);
}