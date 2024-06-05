#include "TextureSampler.h"

#include <iostream>

#include <engine/Window.h>
#include <engine/D3DObjects/RenderingStages.h>

TextureSampler::TextureSampler()
{
	desc =
	{
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_CLAMP,
		0,
		1,
		D3D11_COMPARISON_NEVER,
		{1,1,1,1},
		-FLT_MAX,
		FLT_MAX
	};
}

TextureSampler::TextureSampler(D3D11_SAMPLER_DESC desc, int pipelineStages, unsigned int samplerRegister) :desc{ desc }, pipelineStages{ pipelineStages },samplerRegister { samplerRegister }
{
	createTextureSampler();
}

TextureSampler::~TextureSampler()
{
}

bool TextureSampler::createTextureSampler()
{
	if (usable)
	{
		std::cerr << "Texture sampler already been created\n";
		return true;
	}

	HRESULT errorCode = Window::Instance()->getDevice()->CreateSamplerState(&desc, &oSampler);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create sampler\n";
		return usable = false;
	}
	return usable = true;
}

void TextureSampler::use()
{
	Window* window = Window::Instance();
	if (pipelineStages | Shaders::VERTEX_SHADER)
	{
		window->getDeviceContext()->VSSetSamplers(samplerRegister, 1, oSampler.GetAddressOf());
	}
	if (pipelineStages | Shaders::HULL_SHADER)
	{
		window->getDeviceContext()->HSSetSamplers(samplerRegister, 1, oSampler.GetAddressOf());
	}
	if (pipelineStages | Shaders::DOMAIN_SHADER)
	{
		window->getDeviceContext()->DSSetSamplers(samplerRegister, 1, oSampler.GetAddressOf());
	}
	if (pipelineStages | Shaders::GEOMETRY_SHADER)
	{
		window->getDeviceContext()->GSSetSamplers(samplerRegister, 1, oSampler.GetAddressOf());
	}
	if (pipelineStages | Shaders::PIXEL_SHADER)
	{
		window->getDeviceContext()->PSSetSamplers(samplerRegister, 1, oSampler.GetAddressOf());
	}
}

