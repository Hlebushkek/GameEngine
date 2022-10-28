#include "../include/Layer.hpp"

namespace Engine
{
    Layer::Layer(const char* name)
	{
        this->layerName = name;
    }

    Layer::~Layer() {};
}