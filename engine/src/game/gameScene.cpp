#include "gameScene.h"

#include <iostream>

#include <engine/VertexLayout.h>

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

void GameScene::update(float deltaTime)
{
	sumTime += deltaTime;
	window->pollEvents();

	mesh.position.x = sin(sumTime);

	mesh.rotation.x = sin(sumTime) * 2 * 3.14159f;

	mesh.updateTransformationMatrix();
}

void GameScene::render(float deltaTime)
{
	beginDraw();

	pipeline.bindShaders();
	mesh.setBuffers();

	window->getDeviceContext()->DrawIndexed(3, 0, 0);

	endDraw();
}
