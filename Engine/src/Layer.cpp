#include "../include/Layer.hpp"

namespace Engine
{
    Layer::Layer(const char* name)
	{
        this->layerName = name;
    }

    void Layer::Render(Shader* shader)
    {
        for (GameObject* object : this->renderableObjects)
            object->Render(shader);
    }

    void Layer::RenderUI(Shader* shader)
    {
        for (UIObject* object : this->uiObjects)
            object->Render(shader);
    }

    Layer::~Layer()
    {
        for (GameObject* object : this->renderableObjects)
            delete object;

        for (UIObject* object : this->uiObjects)
            delete object;
    };
}