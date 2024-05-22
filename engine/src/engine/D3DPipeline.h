#pragma once

#include <d3d11.h>
#include <string>
#include <wrl.h>

#include <engine/VertexLayout.h>

class D3DPipeline
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//D3DPipeline(const std::wstring& vertexShaderPath, const std::wstring& fragmentShaderPath, D3D_PRIMITIVE_TOPOLOGY primitiveType, ComPtr<ID3D11InputLayout> inputLayout);
	//D3DPipeline(const std::wstring& vertexShaderPath, const std::wstring& fragmentShaderPath, D3D_PRIMITIVE_TOPOLOGY primitiveType, D3D11_INPUT_ELEMENT_DESC* layoutDescriptions, int layoutDescriptionCount);
	D3DPipeline(D3D_PRIMITIVE_TOPOLOGY primitiveType);
	~D3DPipeline();

	bool addVertexShader(const std::wstring& vertexShaderPath);
	bool addFragmentShader(const std::wstring& fragmentShaderPath);

	bool addLayoutDescription(VertexLayout& layout);

	void bindShaders();

	const ComPtr<ID3DBlob>& getVSByteCode(){return VSByteCode; }
	const ComPtr<ID3D11InputLayout> getInputLayout() { return inputLayout; }
protected:
	//Set to false if shader fails to compile
	bool usable{};

	//Shader objects
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;

	//Vertex shader bytecode
	ComPtr<ID3DBlob> VSByteCode;

	ComPtr<ID3D11InputLayout> inputLayout;

	D3D11_PRIMITIVE_TOPOLOGY primitiveType;

	bool compileShader(const std::wstring& filePath, ComPtr<ID3DBlob>& shaderByteCode,  const std::string& profile, const std::string& entryFunction = "Main");
};