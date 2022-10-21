#include "../include/Layer.hpp"

namespace Engine
{

    Layer::Layer(const char* name)
	{
        this->layerName = name;
    }

    Layer::~Layer() {};

    void Layer::OnAttach() {}
    void Layer::OnDetach() {}
    void Layer::Update() {}
    void Layer::OnEvent(Event& event) {}

}