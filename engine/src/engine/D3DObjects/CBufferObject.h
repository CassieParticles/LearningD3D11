#pragma once

#include <d3d11.h>
#include <wrl.h>

#include <engine/D3DObjects/PipelineBinding.h>


class CBufferObject
{
public:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	CBufferObject();
	~CBufferObject();

	void addBuffer(ComPtr<ID3D11Buffer> buffer, int shaders, unsigned int shaderRegister);
	void addBuffer(D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size, int shaders, unsigned int shaderRegister);
	void addBuffer(void* data, bool dynamic, int size, int shaders, unsigned int shaderRegister);

	void bindBuffer();

	ComPtr<ID3D11Buffer>& getBuffer() { return constantBuffer; }
protected:
	ComPtr<ID3D11Buffer> constantBuffer;
	int shadersBoundTo;
	unsigned int shaderRegister;
	
};