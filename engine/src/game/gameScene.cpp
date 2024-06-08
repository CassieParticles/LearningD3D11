#include "gameScene.h"

#include <iostream>

#include <engine/TimeManager.h>
#include <engine/D3DObjects/VertexLayout.h>
#include <engine/Input.h>

#include <engine/AssetManager.h>

//TODO:
//Reduce repeat code with objects that are bound to stages of pipeline (composition probably better)

GameScene::GameScene(const std::string& sceneName, Window* window, DirectX::XMFLOAT3 bgColour) :BaseScene(sceneName, window, bgColour), pipeline{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST }
{
	mesh.addVertexBuffer(vertices,false,sizeof(vertices),3 * sizeof(float),0);
	mesh.addVertexBuffer(colours, false, sizeof(colours), 3 * sizeof(float), 0);
	mesh.addVertexBuffer(indices, false, sizeof(indices), sizeof(int), 0);

	mesh.addIndexBuffer(indices, false, sizeof(indices), 0);

	pipeline.addVertexShader(L"shaders/vertex.hlsl");
	pipeline.addFragmentShader(L"shaders/fragment.hlsl");

	VertexLayout layout{};

	layout.addVertexComponent("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	layout.addVertexComponent("COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	layout.addVertexComponent("SV_VertexID", 0, DXGI_FORMAT_R32_UINT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

	pipeline.addLayoutDescription(layout);

	player.createProjectionMatrixFOV(90 * 3.14159 * (1.f / 180), window->getAspectRatio(), 0.1f, 1000.f);
	mesh.position.z = 15.0f;

	rasterizerState.setCullMode(D3D11_CULL_NONE);
	rasterizerState.createRasterizerState();
	rasterizerState.use();
	
	Input::Instance()->enableCentredCursor();

	ImageTexture* image = AssetManager::Instance()->getTexture("assets/trans.png");

	image->setStages(Shaders::PIXEL_SHADER);
	image->setSamplerRegister(0);

	sampler.setStages(Shaders::PIXEL_SHADER);
	sampler.setSamplerRegister(0);

	sampler.createTextureSampler();

	D3D11_BUFFER_DESC bufferDesc;

	bufferDesc.ByteWidth = sizeof(float) * 3;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = sizeof(float);
	bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.CPUAccessFlags = 0;
	
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = brightness;

	HRESULT errorCode = window->getDevice()->CreateBuffer(&bufferDesc, &dat, &buffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create buffer\n";
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = DXGI_FORMAT_UNKNOWN;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	viewDesc.Buffer.FirstElement = 0;
	viewDesc.Buffer.NumElements = 3;

	errorCode = window->getDevice()->CreateShaderResourceView(buffer.Get(), &viewDesc, &srv);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create SRV\n";
	}
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
	window->getDeviceContext()->VSSetShaderResources(0, 1, srv.GetAddressOf());

	AssetManager::Instance()->getTexture("assets/trans.png")->use();
	sampler.use();

	window->getDeviceContext()->DrawIndexed(3, 0, 0);

	endDraw();
}
