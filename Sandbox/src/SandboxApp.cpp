#include <Engine.hpp>

class Sandbox : public Engine::Application
{
public:
    Sandbox(const char* title, const int width, const int height) : Engine::Application(title, width, height) {}
    ~Sandbox() {}
};

Engine::Application* Engine::CreateApplication()
{
    return new Sandbox("MineEngine", 600, 400);
}