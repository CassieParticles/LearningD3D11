#pragma once

#include <string>
#include <vector>

class BaseScene;
class TimeManager;

class SceneManager
{
public:
	void update(TimeManager* timeManager);
	void render(TimeManager* timeManager);

	void addScene(BaseScene* scene);
	void changeScene(int newScene);
	void changeScene(const std::string& newScene);

protected:
	std::vector<BaseScene*> scenes;
	int currentScene{};
};