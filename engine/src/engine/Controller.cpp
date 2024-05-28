#include "Controller.h"

#include <glfw3.h>

#include <engine/TimeManager.h>
#include <engine/Input.h>

Controller::Controller(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation):Camera(position,rotation)
{
	input = Input::Instance();

	controls = Controls
	{
		GLFW_KEY_W,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_R,
		GLFW_KEY_F
	};
}

Controller::~Controller()
{
}

void Controller::update(TimeManager* timeManager)
{
	DirectX::XMVECTOR positionStore = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR translation{};
	
	float cosAngle = cos(rotation.y);
	float sinAngle = sin(rotation.y);

	if (input->getKeyDown(controls.forward))
	{
		translation = DirectX::XMVectorAdd(translation, { -sinAngle,0,cosAngle });
	}
	if (input->getKeyDown(controls.left))
	{
		translation = DirectX::XMVectorAdd(translation, { -cosAngle,0,-sinAngle });
	}
	if (input->getKeyDown(controls.right))
	{
		translation = DirectX::XMVectorAdd(translation, { cosAngle,0,sinAngle });
	}
	if (input->getKeyDown(controls.backward))
	{
		translation = DirectX::XMVectorAdd(translation, { sinAngle,0,-cosAngle });
	}

	if (input->getKeyDown(controls.up))
	{
		translation = DirectX::XMVectorAdd(translation, { 0,1,0 });
	}
	if (input->getKeyDown(controls.down))
	{
		translation = DirectX::XMVectorAdd(translation, { 0,-1,0 });
	}
	float deltaTime = timeManager->DeltaTime();

	translation = DirectX::XMVectorScale(translation, deltaTime);

	positionStore = DirectX::XMVectorAdd(positionStore, translation);

	DirectX::XMStoreFloat3(&position, positionStore);
}
