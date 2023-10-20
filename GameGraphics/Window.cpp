#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GameEngine/Engine.h"
#include "GameGraphics/Gizmos.h"
#include "GameGraphics/Color4.h"

inline GameMath::Vector4 UIntToV4(unsigned int value)
{
	GameMath::Vector4 output;

	output.x = ((value & 0xFF000000) >> 24) / 255.0f;
	output.y = ((value & 0x00FF0000) >> 16) / 255.0f;
	output.z = ((value & 0x0000FF00) >> 8) / 255.0f;
	output.w = ((value & 0x000000FF)) / 255.0f;

	return output;
}

void error_callback(int error, const char* description)
{
	std::cout << description << std::endl;
}

GameGraphics::Window::Window(int height, int width, const char* title)
{	
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW library." << std::endl;
		return;
	}

	m_height = height;
	m_width = width;
	m_title = title;

	glfwSetErrorCallback(error_callback);
}

bool GameGraphics::Window::getShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

int GameGraphics::Window::getFrameRate()
{
	return 0;
}

void GameGraphics::Window::setTargetFrameRate(int frameRate)
{

}

void GameGraphics::Window::beginDrawing(GameGraphics::Color4 color)
{
	glClearColor(color.getR(), color.getG(), color.getB(), color.getA());
	glClear(GL_COLOR_BUFFER_BIT);
}

void GameGraphics::Window::endDrawing()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GameGraphics::Window::open()
{
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

	if (!m_window)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	//bind the open gl functions using the address of the glfw process
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return;
	}

	glViewport(0, 0, m_width, m_height);

	GameGraphics::Gizmos::init();
}

void GameGraphics::Window::close()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

GameMath::Vector2 GameGraphics::Window::convertToScreenPosition(GameMath::Vector2 position)
{
	float halfWidth = GameEngine::Engine::getWindow()->getWidth() / 2.0f;
	float halfHeight = GameEngine::Engine::getWindow()->getHeight() / 2.0f;

	return GameMath::Vector2(position.x / halfWidth, position.y / halfHeight);
}

GameMath::Vector2 GameGraphics::Window::convertToWorldPosition(float x, float y)
{
	float halfWidth = GameEngine::Engine::getWindow()->getWidth() / 2.0f;
	float halfHeight = GameEngine::Engine::getWindow()->getHeight() / 2.0f;

	return GameMath::Vector2(x * halfWidth, y * halfHeight);
}
