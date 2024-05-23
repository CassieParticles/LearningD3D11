#pragma once

#include <engine/Window.h>

class TimeManager;

class BaseScene
{
public:
	BaseScene(const std::string& name, Window* window, DirectX::XMFLOAT3 bgColour) :sceneName{ sceneName },window { window }, bgColour{ bgColour } {}
	~BaseScene() {}

	virtual void open() = 0;

	virtual void update(TimeManager* timeManager) = 0;
	virtual void render(TimeManager* timeManager) = 0;

	virtual void close() = 0;

	const std::string& getName() { return sceneName; }
protected:
	std::string sceneName;

	Window* window;

	DirectX::XMFLOAT3 bgColour;

	void beginDraw();
	void endDraw();
	
};