#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

void GameGraphics::Window::beginDrawing(unsigned int color)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
}

void GameGraphics::Window::close()
{
		
}