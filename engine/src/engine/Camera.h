#pragma once

#include <DirectXMath.h>

#include <engine/Window.h>
#include <engine/CBufferObject.h>

class Camera
{
public:
	Camera(DirectX::XMFLOAT3 position = DirectX::XMFLOAT3{}, DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3{});
	~Camera();

	void createProjectionMatrixNP(float viewWidth, float viewHeight, float nearZ, float farZ);
	void createProjectionMatrixFOV(float fov, float aspectRatio, float nearZ, float farZ);
	void createOrthographicMatrix(float viewWidth, float viewHeight, float nearZ, float farZ);

	DirectX::XMMATRIX createViewMatrix();

	void setPosition(DirectX::XMFLOAT3 position) { this->position = position; }
	void setRotation(DirectX::XMFLOAT3 rotation) { this->rotation = rotation; }

	void updateCameraBuffer();
protected:

	//Define if the camera is projection or orthographic
	bool projection;	

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	//Matrix for transforming world into 
	DirectX::XMMATRIX cameraMatrix;

	//Constant buffer for storing camera matrix
	CBufferObject cameraBuffer;
};