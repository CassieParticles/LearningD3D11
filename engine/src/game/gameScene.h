#pragma once
#include <engine/BaseScene.h>
#include <engine/Controller.h>
#include <engine/D3DObjects/GameObject.h>
#include <engine/D3DObjects/D3DPipeline.h>
#include <engine/D3DObjects/RasterizerState.h>

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
		0.f,0.5f,.0f,
		-0.5f,-0.5f,.0f,
		0.5f,-0.5f,.0f
	};

	float colours[9] =
	{
		.5f,1.f,0,
		0.f,0.f,0,
		1.f,0.f,0
	};

	int indices[3] =
	{
		0,2,1
	};

	float* textureData;

	Controller player;
	GameObject mesh;
	D3DPipeline pipeline;
	RasterizerState rasterizerState;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};
