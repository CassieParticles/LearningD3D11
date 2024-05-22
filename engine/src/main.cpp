#include <iostream>

#include <engine/Window.h>
#include <engine/SceneManager.h>

#include <game/gameScene.h>

int main()
{
	Window* window = Window::initializeWindow("Window", 800, 800);
	SceneManager sceneManager;

	sceneManager.addScene(new GameScene("Main scene", window, DirectX::XMFLOAT3(.0f, .6f, .6f)));
	
	while (!window->windowShouldClose())
	{
		sceneManager.update(0.001f);
		sceneManager.render(0.001f);
	}

	return 0;
}