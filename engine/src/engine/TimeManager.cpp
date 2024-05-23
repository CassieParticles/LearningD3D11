#include "TimeManager.h"

#include <glfw3.h>

#include <engine/Window.h>


TimeManager::TimeManager(Window* window) :window{ window },previousTime {}, currentTime{}, elapsedTime{}
{
}

void TimeManager::Start()
{
	elapsedTime = 0;
	previousTime = glfwGetTime();
	currentTime = glfwGetTime();
	frameCount = 0;
}

void TimeManager::Tick()
{
	previousTime = currentTime;
	currentTime = glfwGetTime();
	elapsedTime += deltaTime();
	++frameCount;
}

double TimeManager::deltaTime()
{
	return currentTime - previousTime;
}

double TimeManager::FPS()
{
	return frameCount / elapsedTime;
}

double TimeManager::MSPF()
{
	return 1000.0 / FPS();
}

double TimeManager::ElapsedTime()
{
	return elapsedTime;
}
