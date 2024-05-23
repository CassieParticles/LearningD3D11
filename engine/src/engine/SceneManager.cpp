#include "SceneManager.h"

#include <engine/BaseScene.h>

void SceneManager::update(TimeManager* timeManager)
{
	scenes.at(currentScene)->update(timeManager);
}

void SceneManager::render(TimeManager* timeManager)
{
	scenes.at(currentScene)->render(timeManager);
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
