#pragma once
#include <engine/Camera.h>

class Input;
class TimeManager;

class Controller:public Camera
{
public:
	struct Controls
	{
		int forward;
		int left; 
		int backward;
		int right;

		int up;
		int down;
	};

	Controller(DirectX::XMFLOAT3 position = DirectX::XMFLOAT3{}, DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3{});
	~Controller();

	void update(TimeManager* timeManager);

protected:
	Input* input; 

	Controls controls;
};