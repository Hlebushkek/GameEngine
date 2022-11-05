#include <Engine.hpp>
#include <include/EntryPoint.hpp>
#include "../include/SandBox.hpp"
#include "../include/BackgroundLayer.hpp"
#include "../include/InterfaceLayer.hpp"
#include "../include/ChunkRenderer.hpp"


SandBox::SandBox(const char* title, const int width, const int height)
    : Engine::Application(title, width, height)
{
    BackgroundLayer* backgroundLayer = new BackgroundLayer();
    PushLayer(backgroundLayer);

    ChunkRenderer* chunk = new ChunkRenderer(glm::uvec3(8, 8, 8));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                backgroundLayer->AddRenderableObject(chunk->meshArray[i][j][k]);
            }
        }
    }

    InterfaceLayer* interfaceLayer = new InterfaceLayer();
    PushLayer(interfaceLayer);
}

Engine::Application* Engine::CreateApplication()
{
    return new SandBox("MineEngine", 600, 400);
}