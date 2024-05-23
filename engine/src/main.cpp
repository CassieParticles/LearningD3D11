#include <iostream>

#include <engine/Window.h>
#include <engine/SceneManager.h>
#include <engine/TimeManager.h>

#include <game/gameScene.h>

int main()
{
	Window* window = Window::initializeWindow("Window", 800, 800);
	TimeManager timeManager{window};
	SceneManager sceneManager;

	sceneManager.addScene(new GameScene("Main scene", window, DirectX::XMFLOAT3(.0f, .6f, .6f)));
	

	timeManager.Start();
	while (!window->windowShouldClose())
	{
		timeManager.Tick();
		sceneManager.update(&timeManager);
		sceneManager.render(&timeManager);
	}

	std::cout << "Average fps = " << timeManager.FPS()<<'\n';

	return 0;
}