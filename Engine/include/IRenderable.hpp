#pragma once

namespace Engine
{
    class Shader;

    class IRenderable
    {
    public:
        virtual ~IRenderable() {}
        virtual void Render(Shader* shader) = 0;
    };
}
