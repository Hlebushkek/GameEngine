#include "../include/LayerStack.hpp"

namespace Engine {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerCounter, layer);
		layerCounter++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.begin() + layerCounter, layer);
		if (it != layers.begin() + layerCounter)
		{
			layer->OnDetach();
			layers.erase(it);
			layerCounter--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers.begin() + layerCounter, layers.end(), overlay);
		if (it != layers.end())
		{
			overlay->OnDetach();
			layers.erase(it);
		}
	}

}