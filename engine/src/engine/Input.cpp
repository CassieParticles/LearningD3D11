#include "Input.h"

#include <glfw3.h>

#include <engine/Window.h>

Input* Input::instance{};

Input* Input::InitializeInput()
{
	return instance = new Input();
}

void Input::update()
{
	//Poll events to get key inputs
	glfwPollEvents();

	//Swap arrays, so prev array is last frame's keys, better then copying current to prev every frame
	bool* tempPtr = keyStatesPrev;
	keyStatesPrev = keyStatesCurrent;
	keyStatesCurrent = tempPtr;

	//Update current array with this frame's inputs
	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		keyStatesCurrent[i] = glfwGetKey(window->getWindow(), i);
	}

	double x, y;
	glfwGetCursorPos(window->getWindow(), &x, &y);

	if (cursorCentred)
	{
		glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);

		mousePosition.x = x - window->getWidth() / 2;
		mousePosition.y = y - window->getHeight() / 2;
	}
	else
	{
		mousePosition.x = x;
		mousePosition.y = y;
	}
}

bool Input::getKeyDown(int key)
{
	return keyStatesCurrent[key];
}

bool Input::getKeyPressed(int key)
{
	return keyStatesCurrent[key] && !keyStatesPrev[key];
}

bool Input::getKeyReleased(int key)
{
	return !keyStatesCurrent[key] && keyStatesPrev[key];
}

Input::Input()
{
	keyStatesCurrent = new bool[GLFW_KEY_LAST];
	keyStatesPrev = new bool[GLFW_KEY_LAST];
	window = Window::Instance();
	cursorCentred = false;
}

Input::~Input()
{
	delete[] keyStatesCurrent;
	delete[] keyStatesPrev;
}
