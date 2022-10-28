#pragma once
#include <Engine.hpp>

class BackgroundLayer : public Engine::Layer
{
public:
	BackgroundLayer();
	virtual ~BackgroundLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
    virtual void Update() override;
	virtual void OnImGuiRender() override;

private:
	glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f };

};