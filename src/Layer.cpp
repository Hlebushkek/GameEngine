#include "Layer.hpp"

namespace Engine
{
    Layer::Layer(const char* name)
	{
        this->layerName = name;
    }

    std::optional<Intersection> Layer::CheckRayCast(const Ray& ray, const std::vector<int>& buttons)
    {
        std::optional<Intersection> result = std::nullopt;

        for (GameObject* object : this->renderableObjects)
        {
            auto intersection = object->CollidesWith(ray);
            if (intersection.has_value())
                if (result == std::nullopt || glm::distance(intersection.value().point, ray.origin) < glm::distance(result.value().point, ray.origin))
                    result = intersection;
        }

        return result;
    }

    void Layer::CheckCollisions()
    {
        //Check collision between objects
    }

    void Layer::Render(Shader *shader)
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
    }
}