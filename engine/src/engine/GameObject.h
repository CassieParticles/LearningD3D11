#pragma once
#include <engine/Mesh.h>

#include <DirectXMath.h>

class GameObject :public Mesh
{
public:
	GameObject(DirectX::XMFLOAT3 position = DirectX::XMFLOAT3{}, DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3{}, DirectX::XMFLOAT3 scale = DirectX::XMFLOAT3{1.f,1.f,1.f});
	~GameObject();

	//Update buffer for rendering, do this at end of moving object
	void updateTransformationMatrix();

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
protected:

	DirectX::XMMATRIX getTransformationMatrix();

	ComPtr<ID3D11Buffer> transformationCBuffer;
};