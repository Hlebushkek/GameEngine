#include "../include/Layer.hpp"

namespace Engine
{
    Layer::Layer(const char* name)
	{
        this->layerName = name;
    }

    void Layer::Render(Shader* shader)
    {
        for (IRenderable* object : this->renderableObjects)
            object->Render(shader);
    }

    Layer::~Layer()
    {
        for (IRenderable* object : this->renderableObjects)
            delete object;
    };
}