#include "GameObject.h"

#include <engine/Window.h>

GameObject::GameObject(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale) :Mesh(), position{ position }, rotation{ rotation },scale{scale}
{
	//addConstantBuffer((D3D11_SUBRESOURCE_DATA*)nullptr, true, sizeof(DirectX::XMMATRIX));
	//transformationCBuffer = constantBuffers[0];

	transformationCBuffer.addBuffer((D3D11_SUBRESOURCE_DATA*)nullptr, true, sizeof(DirectX::XMMATRIX), Shaders::VERTEX_SHADER | Shaders::PIXEL_SHADER, 2);
}

GameObject::~GameObject()
{
}

void GameObject::updateTransformationMatrix()
{
	DirectX::XMMATRIX mat = getTransformationMatrix();

	D3D11_MAPPED_SUBRESOURCE transformationMap{};
	Window* window = Window::Instance();

	window->getDeviceContext()->Map(transformationCBuffer.getBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &transformationMap);

	memcpy(transformationMap.pData, &mat, sizeof(mat));

	window->getDeviceContext()->Unmap(transformationCBuffer.getBuffer().Get(), 0);

}

void GameObject::setBuffers()
{
	transformationCBuffer.bindBuffer();
	Mesh::setBuffers();
}

DirectX::XMMATRIX GameObject::getTransformationMatrix()
{
	//Get rotation matrix
	DirectX::XMMATRIX mat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	mat = mat * DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	mat = mat * DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	return mat;
}
