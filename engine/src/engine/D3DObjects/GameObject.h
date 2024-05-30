#pragma once
#include <engine/D3DObjects/Mesh.h>

#include <DirectXMath.h>

#include <engine/D3DObjects/CBufferObject.h>

class GameObject :public Mesh
{
public:
	GameObject(DirectX::XMFLOAT3 position = DirectX::XMFLOAT3{}, DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3{}, DirectX::XMFLOAT3 scale = DirectX::XMFLOAT3{1.f,1.f,1.f});
	~GameObject();

	//Update buffer for rendering, do this at end of moving object
	void updateTransformationMatrix();

	void setBuffers() override;

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
protected:

	DirectX::XMMATRIX getTransformationMatrix();

	//ComPtr<ID3D11Buffer> transformationCBuffer;
	CBufferObject transformationCBuffer;
};