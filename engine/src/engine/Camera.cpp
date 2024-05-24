#include "Camera.h"


Camera::Camera(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation) :position{ position }, rotation{ rotation }, projection{}, cameraMatrix{}
{
	//VS register 1 is used for camera
	cameraBuffer.addBuffer((D3D11_SUBRESOURCE_DATA*)nullptr, true, sizeof(DirectX::XMMATRIX), Shaders::VERTEX_SHADER, 1);
	cameraBuffer.bindBuffer();
}

Camera::~Camera()
{
}

void Camera::createProjectionMatrixNP(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	cameraMatrix = DirectX::XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ);
	projection = true;
	updateCameraBuffer();
}

void Camera::createProjectionMatrixFOV(float fov, float aspectRatio, float nearZ, float farZ)
{
	cameraMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
	projection = true;
	updateCameraBuffer();
}

void Camera::createOrthographicMatrix(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	cameraMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
	projection = false;
	updateCameraBuffer();
}

DirectX::XMMATRIX Camera::createViewMatrix()
{
	DirectX::XMVECTOR viewDirection = { cos(rotation.x) * sin(rotation.y),sin(rotation.x),cos(rotation.x) * cos(rotation.y) };
	return DirectX::XMMatrixLookToLH(DirectX::XMVECTOR{position.x,position.y,position.z}, viewDirection, DirectX::XMVECTOR{0, 1, 0});
}

void Camera::updateCameraBuffer()
{
	DirectX::XMMATRIX viewMatrix = createViewMatrix();
	DirectX::XMMATRIX matrix = viewMatrix * cameraMatrix;
	D3D11_MAPPED_SUBRESOURCE transformationMap{};
	Window* window = Window::Instance();

	window->getDeviceContext()->Map(cameraBuffer.getBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &transformationMap);
	memcpy(transformationMap.pData, &matrix, sizeof(matrix));
	window->getDeviceContext()->Unmap(cameraBuffer.getBuffer().Get(), 0);
}

