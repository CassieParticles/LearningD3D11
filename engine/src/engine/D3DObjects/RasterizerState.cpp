#include "RasterizerState.h"

#include <iostream>

#include <engine/Window.h>

RasterizerState::RasterizerState()
{
	//Set default values
	desc = 
	{
	D3D11_FILL_SOLID,	//Fill mode solid
	D3D11_CULL_BACK,	//Cull back faces
	false,				//CCW faces aren't front faces
	0,					//Depth bias
	0,					//Depth bias clamp
	0,					//SlopeScaledDepthBias
	true,				//Clip pixels based on depth
	false,				//Disable scissor test
	false,				//Disable multisampling
	false				//Disable antialiasedLines
	};
}

RasterizerState::RasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool frontFaceCCW, int depthBias, float depthBiasClamp, float slopeScaledDepthBias, bool depthClipEnable, bool scissorTest, bool multisampleEnable, bool antialiasLineEnable)
{
	desc = 
	{
	fillMode,
	cullMode,
	frontFaceCCW,
	depthBias,
	depthBiasClamp,
	slopeScaledDepthBias,
	depthClipEnable,
	scissorTest,
	multisampleEnable,
	antialiasLineEnable,
	};

	//Since parameters already set, craete sampler state now
	createSamplerState();
}

bool RasterizerState::createSamplerState()
{
	HRESULT err = Window::Instance()->getDevice()->CreateRasterizerState(&desc, &rasterizerState);
	if (FAILED(err))
	{
		std::cerr << "Failed to create rasterizer state\n";
		return usable = false;
	}
	return usable = true;
}

void RasterizerState::use()
{
	Window::Instance()->getDeviceContext()->RSSetState(rasterizerState.Get());
}
