#pragma once

#include "Layer.hpp"
#include <vector>

namespace Engine
{

    class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(std::shared_ptr<Layer> layer);
    	void PushOverlay(std::shared_ptr<Layer> overlay);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> overlay);

		auto begin() { return layers.begin(); }
		auto end() { return layers.end(); }
		auto rbegin() { return layers.rbegin(); }
		auto rend() { return layers.rend(); }

		auto begin() const { return layers.begin(); }
		auto end() const { return layers.end(); }
		auto rbegin() const { return layers.rbegin(); }
		auto rend() const { return layers.rend(); }

		std::shared_ptr<Layer> back() const { return layers.back(); }
	private:
		std::vector<std::shared_ptr<Layer>> layers;
		unsigned int layerCounter = 0;
	};

}