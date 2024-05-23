#pragma once
#include <engine/BaseScene.h>
#include <engine/GameObject.h>
#include <engine/D3DPipeline.h>

class TimeManager;


class GameScene :public BaseScene
{
public:
	GameScene(const std::string& sceneName, Window* window, DirectX::XMFLOAT3 bgColour);
	~GameScene();

	void open() override;
	void close() override;

	void update(TimeManager* timeManager);
	void render(TimeManager* timeManager);
protected:
	float vertices[9] = 
	{
		0.f,0.5f,.5f,
		-0.5f,-0.5f,.5f,
		0.5f,-0.5f,.5f
	};

	float colours[9] =
	{
		1,0,0,
		0,1,0,
		0,0,1
	};

	int indices[3] =
	{
		0,2,1
	};

	GameObject mesh;
	D3DPipeline pipeline;

	float sumTime{};
};
