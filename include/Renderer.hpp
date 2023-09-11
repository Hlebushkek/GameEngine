#pragma once

#include <memory>

struct SDL_Window;
struct ImGuiContext;

namespace Engine
{

class Layer;
class Shader;
class Mesh;
class Primitive;

struct RenderingContext;

class Renderer
{
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void UseShader(Shader* shader);

    void SetOnlyWireframeMode(bool value);

    void PreRenderSetup();
    void RenderLayer(Layer* layer);
    void PostRenderSetup();

    void PreImGuiRenderSetup();
    void PostImGuiRenderSetup();

    static RenderingContext* GetRenderingContext() { return m_renderingContext; }

private:
    static RenderingContext* m_renderingContext;

private:
    class Impl;
    std::unique_ptr<Impl> impl;

};

}