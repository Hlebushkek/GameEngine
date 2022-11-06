#pragma once

namespace Engine
{
    class Shader;

    class ENGINE_API IRenderable
    {
    public:
        virtual ~IRenderable() {}
        virtual void Render(Shader* shader) = 0;
    };
}
