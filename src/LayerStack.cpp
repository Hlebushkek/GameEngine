#include "LayerStack.hpp"

namespace Engine {

	LayerStack::~LayerStack()
	{
		for (const auto& layer : layers)
		{
			layer->OnDetach();
		}
	}

	void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		layers.emplace(layers.begin() + layerCounter, std::move(layer));
		++layerCounter;
	}

	void LayerStack::PushOverlay(std::shared_ptr<Layer> overlay)
	{
		layers.emplace_back(std::move(overlay));
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
	{
		auto it = std::find(layers.begin(), layers.begin() + layerCounter, layer);
		if (it != layers.begin() + layerCounter)
		{
			(*it)->OnDetach();
			layers.erase(it);
			--layerCounter;
		}
	}

	void LayerStack::PopOverlay(std::shared_ptr<Layer> overlay)
	{
		auto it = std::find(layers.begin() + layerCounter, layers.end(), overlay);
		if (it != layers.end())
		{
			(*it)->OnDetach();
			layers.erase(it);
		}
	}

}