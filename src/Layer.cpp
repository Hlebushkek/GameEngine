#include "Renderer.hpp"
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

        for (auto object : renderableObjects)
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

    void Layer::Render(Renderer* renderer, Shader* shader)
    {
        for (auto object : renderableObjects)
            object->Render(renderer, shader);
    }

    void Layer::RenderUI(Renderer* renderer, Shader* shader)
    {
        for (auto object : uiObjects)
            object->Render(shader);
    }

    Layer::~Layer()
    {
        for (UIObject* object : this->uiObjects)
            delete object;
    }
}
