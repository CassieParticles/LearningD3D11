#pragma once



#include <wrl.h>
#include <d3d11.h>
#include <engine/D3DObjects/PipelineBinding.h>

struct ImageData;

class ImageTexture
{
public:
	ImageTexture(ImageData* imageData);
	~ImageTexture();

	void setStages(int stages) { pipelineStages = pipelineStages | stages; }
	void resetStages(int stages) { pipelineStages = pipelineStages & (~stages); }
	void setSamplerRegister(int samplerRegister) { samplerRegister = samplerRegister; }

	void use();
protected:
	ImageData* imageData;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV;

	int pipelineStages{};
	unsigned int samplerRegister{};
};