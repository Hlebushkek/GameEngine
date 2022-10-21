#pragma once

#ifdef _WIN32

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif