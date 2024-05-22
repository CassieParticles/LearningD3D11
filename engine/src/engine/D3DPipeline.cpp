#include "D3DPipeline.h"

#include <iostream>
#include <d3dcompiler.h>

#include <engine/Window.h>

//
//D3DPipeline::D3DPipeline(const std::wstring& vertexShaderPath, const std::wstring& fragmentShaderPath, D3D_PRIMITIVE_TOPOLOGY primitiveType, D3D11_INPUT_ELEMENT_DESC* layoutDescriptions, int layoutDescriptionCount):primitiveType{primitiveType}
//{
//	//Compile shaders
//	Window* window = Window::Instance();
//	if (compileShader(vertexShaderPath, VSByteCode, "vs_5_0"))
//	{
//		if (FAILED(window->getDevice()->CreateVertexShader(VSByteCode->GetBufferPointer(), VSByteCode->GetBufferSize(), nullptr, &vertexShader)))
//		{
//			std::cerr << "Failed to create vertex shader\n";
//			return;
//		}
//	}
//
//	ComPtr<ID3DBlob> PSByteCode = nullptr;
//	if (compileShader(fragmentShaderPath, PSByteCode, "ps_5_0"))
//	{
//		if (FAILED(window->getDevice()->CreatePixelShader(PSByteCode->GetBufferPointer(), PSByteCode->GetBufferSize(), nullptr, &pixelShader)))
//		{
//			std::cerr << "Failed to create pixel shader\n";
//			return;
//		}
//	}
//
//
//	//Create input layout
//	HRESULT errorCode = window->getDevice()->CreateInputLayout(layoutDescriptions, layoutDescriptionCount, VSByteCode->GetBufferPointer(), VSByteCode->GetBufferSize(), &inputLayout);
//	if (FAILED(errorCode))
//	{
//		std::cerr << "Failed to create input layout\n";
//		return;
//	}
//}



D3DPipeline::D3DPipeline(D3D_PRIMITIVE_TOPOLOGY primitiveType):usable{true},primitiveType{primitiveType}
{
	
}

D3DPipeline::~D3DPipeline()
{
}

bool D3DPipeline::addVertexShader(const std::wstring& vertexShaderPath)
{

	if (compileShader(vertexShaderPath, VSByteCode, "vs_5_0"))
	{
		if (FAILED(Window::Instance()->getDevice()->CreateVertexShader(VSByteCode->GetBufferPointer(), VSByteCode->GetBufferSize(), nullptr, &vertexShader)))
		{
			std::cerr << "Failed to compile vertexShader\n";
			usable = false;
			return false;
		}
	}

	return true;
}

bool D3DPipeline::addFragmentShader(const std::wstring& fragmentShaderPath)
{
	ComPtr<ID3DBlob> PSByteCode;
	
	if (compileShader(fragmentShaderPath, PSByteCode, "ps_5_0"))
	{
		if (FAILED(Window::Instance()->getDevice()->CreatePixelShader(PSByteCode->GetBufferPointer(), PSByteCode->GetBufferSize(), nullptr, &pixelShader)))
		{
			std::cerr << "Failed to create fragment shader\n";
			usable = false;
			return false;
		}
	}

	return true;
}

bool D3DPipeline::addLayoutDescription(VertexLayout& layout)
{
	if (FAILED(Window::Instance()->getDevice()->CreateInputLayout(layout.getLayout(), layout.getSize(), VSByteCode->GetBufferPointer(), VSByteCode->GetBufferSize(), &inputLayout)))
	{
		std::cerr << "Failed to craete input layout\n";
		usable = false;
		return false;
	}
	return true;
}

void D3DPipeline::bindShaders()
{
	if (!usable)
	{
		std::cerr << "Error, pipeline didn't create successfully, do not use\n";
		return;
	}
	Window* window = Window::Instance();
	window->getDeviceContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
	window->getDeviceContext()->PSSetShader(pixelShader.Get(), nullptr, 0);

	window->getDeviceContext()->IASetInputLayout(inputLayout.Get());
	window->getDeviceContext()->IASetPrimitiveTopology(primitiveType);
}

bool D3DPipeline::compileShader(const std::wstring& filePath, ComPtr<ID3DBlob>& shaderByteCode,  const std::string& profile,const std::string& entryFunction )
{
	constexpr UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	ComPtr<ID3DBlob> tempShaderBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

	if (FAILED(D3DCompileFromFile(filePath.data(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryFunction.data(), profile.data(), compileFlags, 0, &tempShaderBlob, &errorBlob)))
	{
		std::cerr << "Failed to compile shader\n";
		if (errorBlob != nullptr)
		{
			std::cerr << "Compilation message: " << static_cast<const char*>(errorBlob->GetBufferPointer()) << "\n";
		}
		return false;
	}

	shaderByteCode = std::move(tempShaderBlob);
	return true;
}
