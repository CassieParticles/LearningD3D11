#include "SceneManager.h"

#include <engine/BaseScene.h>

void SceneManager::update(float deltaTime)
{
	scenes.at(currentScene)->update(deltaTime);
}

void SceneManager::render(float deltaTime)
{
	scenes.at(currentScene)->render(deltaTime);
}

void SceneManager::addScene(BaseScene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::changeScene(int newScene)
{
	if (newScene<0 || newScene>scenes.size()) { return; }
	
	scenes[currentScene]->close();
	currentScene = newScene;
	scenes[currentScene]->open();

}

void SceneManager::changeScene(const std::string& newScene)
{
	for (int i = 0; i < scenes.size(); ++i)
	{
		if (scenes[i]->getName() == newScene)
		{
			changeScene(i);
		}
	}
}
