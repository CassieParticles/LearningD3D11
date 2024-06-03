#include "gameScene.h"

#include <iostream>

#include <engine/TimeManager.h>
#include <engine/D3DObjects/VertexLayout.h>
#include <engine/Input.h>

#include <engine/AssetManager.h>

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

	ImageData* image = AssetManager::Instance()->getImage("assets/trans.png");
	
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = image->width;
	texDesc.Height = image->height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_IMMUTABLE;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	D3D11_TEXTURE2D_DESC* texDescPtr = &texDesc;
	
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = (void*)image->data;
	dat.SysMemPitch = image->width * 4 * sizeof(unsigned char);

	D3D11_SUBRESOURCE_DATA* datPtr = &dat;

	HRESULT errorCode= window->getDevice()->CreateTexture2D(texDescPtr, datPtr, &texture);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create texture\n";
	}

	delete image;

	//Create a SRV for the texture
	
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc{};
	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;
	viewDesc.Texture2D.MostDetailedMip = 0;

	errorCode = window->getDevice()->CreateShaderResourceView(texture.Get(), &viewDesc, &SRV);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create SRV\n";
	}

	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_EQUAL;

	errorCode = window->getDevice()->CreateSamplerState(&samplerDesc, &sampler);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create sampler\n";
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

	window->getDeviceContext()->PSSetShaderResources(0, 1, SRV.GetAddressOf());
	window->getDeviceContext()->PSSetSamplers(0,1,sampler.GetAddressOf());

	window->getDeviceContext()->DrawIndexed(3, 0, 0);

	endDraw();
}
