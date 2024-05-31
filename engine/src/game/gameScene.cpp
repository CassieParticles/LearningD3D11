#include "gameScene.h"

#include <iostream>

#include <engine/TimeManager.h>
#include <engine/D3DObjects/VertexLayout.h>
#include <engine/Input.h>

GameScene::GameScene(const std::string& sceneName, Window* window, DirectX::XMFLOAT3 bgColour) :BaseScene(sceneName, window, bgColour),pipeline{D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST}
{
	mesh.addVertexBuffer(vertices,false,sizeof(vertices),3 * sizeof(float),0);
	mesh.addVertexBuffer(colours, false, sizeof(colours), 3 * sizeof(float), 0);

	mesh.addIndexBuffer(indices, false, sizeof(indices), 0);

	
	pipeline.addVertexShader(L"shaders/vertex.hlsl");
	pipeline.addFragmentShader(L"shaders/fragment.hlsl");

	VertexLayout layout{};

	layout.addVertexComponent("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	layout.addVertexComponent("COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

	pipeline.addLayoutDescription(layout);

	player.createProjectionMatrixFOV(90 * 3.14159 * (1.f / 180), window->getAspectRatio(), 0.1f, 1000.f);
	mesh.position.z = 15.0f;

	rasterizerState.setCullMode(D3D11_CULL_NONE);
	rasterizerState.createRasterizerState();
	rasterizerState.use();
	
	Input::Instance()->enableCentredCursor();
}

GameScene::~GameScene()
{
}

void GameScene::open()
{
}

void GameScene::close()
{
}

void GameScene::update(TimeManager* timeManager)
{

	mesh.rotation.y = timeManager->ElapsedTime();

	player.update(timeManager);

	mesh.updateTransformationMatrix();
	player.updateCameraBuffer();
}

void GameScene::render(TimeManager* timeManager)
{
	beginDraw();

	pipeline.bindShaders();
	mesh.setBuffers();

	window->getDeviceContext()->DrawIndexed(3, 0, 0);

	endDraw();
}
