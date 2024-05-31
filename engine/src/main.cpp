#include <iostream>
#include <glfw3.h>

#include <engine/Window.h>
#include <engine/SceneManager.h>
#include <engine/TimeManager.h>
#include <engine/Input.h>

#include <game/gameScene.h>

int main()
{
	Window* window = Window::initializeWindow("Window", 800, 800);
	Input* input = Input::InitializeInput();
	TimeManager timeManager{window};
	SceneManager sceneManager;
	

	sceneManager.addScene(new GameScene("Main scene", window, DirectX::XMFLOAT3(.0f, .6f, .6f)));
	

	timeManager.Start();
	while (!window->windowShouldClose())
	{
		timeManager.Tick();
		input->update();
		sceneManager.update(&timeManager);
		sceneManager.render(&timeManager);

		if (timeManager.DeltaTime() > 0.01)
		{
			std::cout << "Frames dropped below 100\n";
			std::cout << "Frame time: " << timeManager.DeltaTime()<<'\n';
		}

		if (input->getKeyDown(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window->getWindow(),true);
	
		}
	}

	std::cout << "Average fps = " << timeManager.FPS()<<'\n';
	std::cout << "Average mspf = " << timeManager.MSPF()<<'\n';

	return 0;
}