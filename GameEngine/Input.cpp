#include "Input.h"
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "GameGraphics/Window.h""

bool GameEngine::Input::isKeyDown(int key)
{
	return glfwGetKey(Engine::getWindow()->getWindowContext(), key) == GLFW_PRESS;
}

bool GameEngine::Input::isKeyUp(int key)
{
	return glfwGetKey(Engine::getWindow()->getWindowContext(), key) == GLFW_RELEASE;
}

bool GameEngine::Input::isMouseButtonDown(int button)
{
	return glfwGetMouseButton(Engine::getWindow()->getWindowContext(), button) == GLFW_PRESS;
}

bool GameEngine::Input::isMouseButtonUp(int button)
{
	return glfwGetMouseButton(Engine::getWindow()->getWindowContext(), button) == GLFW_RELEASE;
}

GameMath::Vector2 GameEngine::Input::getMousePosition()
{
	double x, y;
	glfwGetCursorPos(Engine::getWindow()->getWindowContext(), &x, &y);
	
	float halfWidth = GameEngine::Engine::getWindow()->getWidth() / 2.0f;
	float halfHeight = GameEngine::Engine::getWindow()->getHeight() / 2.0f;


	return { (float)x - halfWidth,halfHeight - (float)y};
}
