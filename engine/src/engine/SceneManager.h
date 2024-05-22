#pragma once

#include <string>
#include <vector>

class BaseScene;

class SceneManager
{
public:
	void update(float deltaTime);
	void render(float deltaTime);

	void addScene(BaseScene* scene);
	void changeScene(int newScene);
	void changeScene(const std::string& newScene);

protected:
	std::vector<BaseScene*> scenes;
	int currentScene{};
};