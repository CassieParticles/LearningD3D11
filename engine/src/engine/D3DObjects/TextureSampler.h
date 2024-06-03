#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>

class TextureSampler
{
public:
	TextureSampler();
	TextureSampler(D3D11_SAMPLER_DESC desc, int pipelineStages, unsigned int samplerRegister);
	~TextureSampler();

	//Parameters of the description, cannot be updated after sampler creation
	void setFilter(D3D11_FILTER filter) { desc.Filter = filter; }
	void setAddressModeU(D3D11_TEXTURE_ADDRESS_MODE addressMode) { desc.AddressU = addressMode; }
	void setAddressModeV(D3D11_TEXTURE_ADDRESS_MODE addressMode) { desc.AddressV = addressMode; }
	void setAddressModeW(D3D11_TEXTURE_ADDRESS_MODE addressMode) { desc.AddressW = addressMode; }
	void setAddressMode(D3D11_TEXTURE_ADDRESS_MODE addressMode) { desc.AddressU = desc.AddressV = desc.AddressW = addressMode; }
	void setMipLODBias(float bias) { desc.MipLODBias = bias; }
	void setMaxAnistropy(unsigned int MaxAnistropy) { desc.MaxAnisotropy = MaxAnistropy; }
	void setComparisonFunc(D3D11_COMPARISON_FUNC comp) { desc.ComparisonFunc = comp; }
	void setBorderColour(DirectX::XMFLOAT4 colour) { desc.BorderColor[0] = colour.x; desc.BorderColor[1] = colour.y; desc.BorderColor[2] = colour.z; desc.BorderColor[3] = colour.w; }
	void setMinLOD(float minLOD) { desc.MinLOD = minLOD; }
	void setMaxLOD(float maxLOD) { desc.MaxLOD = maxLOD; }

	//Where it's bound, can be updated after sampler creation
	void setStages(int stages) { pipelineStages = pipelineStages | stages; }
	void resetStages(int stages) { pipelineStages = pipelineStages & (~stages); }
	void setSamplerRegister(int samplerRegister) { samplerRegister = samplerRegister; }

	bool createTextureSampler();

	void use();
protected:
	bool usable{};

	D3D11_SAMPLER_DESC desc{};

	Microsoft::WRL::ComPtr<ID3D11SamplerState> oSampler;

	int pipelineStages{};
	unsigned int samplerRegister{};
};