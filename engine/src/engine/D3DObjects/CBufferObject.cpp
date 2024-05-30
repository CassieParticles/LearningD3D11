#include "CBufferObject.h"
#include <engine/Window.h>
#include <iostream>

CBufferObject::CBufferObject()
{
}

CBufferObject::~CBufferObject()
{
}

void CBufferObject::addBuffer(ComPtr<ID3D11Buffer> buffer, int shaders, unsigned int shaderRegister)
{
	constantBuffer = buffer;
	shadersBoundTo = shaders;
	this->shaderRegister = shaderRegister;
}

void CBufferObject::addBuffer(D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size, int shaders, unsigned int shaderRegister)
{
	if (size % 16 != 0)
	{
		std::cerr << "Error, constant buffer not packed properly\n";
		return;
	}
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = size;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
	desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

	ComPtr<ID3D11Buffer> constantBuffer;

	HRESULT errorCode = Window::Instance()->getDevice()->CreateBuffer(&desc, data, &constantBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create constant buffer\n";
		return;
	}

	addBuffer(constantBuffer, shaders, shaderRegister);
}

void CBufferObject::addBuffer(void* data, bool dynamic, int size, int shaders, unsigned int shaderRegister)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;

	addBuffer(&dat, dynamic, size,shaders,shaderRegister);
}

void CBufferObject::bindBuffer()
{
	Window* window = Window::Instance();
	if (shadersBoundTo | Shaders::VERTEX_SHADER)
	{
		window->getDeviceContext()->VSSetConstantBuffers(shaderRegister, 1, constantBuffer.GetAddressOf());
	}
	if (shadersBoundTo | Shaders::HULL_SHADER)
	{
		window->getDeviceContext()->HSSetConstantBuffers(shaderRegister, 1, constantBuffer.GetAddressOf());
	}
	if (shadersBoundTo | Shaders::DOMAIN_SHADER)
	{
		window->getDeviceContext()->DSSetConstantBuffers(shaderRegister, 1, constantBuffer.GetAddressOf());
	}
	if (shadersBoundTo | Shaders::GEOMETRY_SHADER)
	{
		window->getDeviceContext()->GSSetConstantBuffers(shaderRegister, 1, constantBuffer.GetAddressOf());
	}
	if (shadersBoundTo | Shaders::PIXEL_SHADER)
	{
		window->getDeviceContext()->PSSetConstantBuffers(shaderRegister, 1, constantBuffer.GetAddressOf());
	}
}

