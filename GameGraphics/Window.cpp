#include "Window.h"
#include <Raylib/raylib.h>

GameGraphics::Window::Window(int height, int width, const char* title)
{
	m_height = height;
	m_width = width;
	m_title = title;
}

bool GameGraphics::Window::getShouldClose()
{
	return WindowShouldClose();
}

int GameGraphics::Window::getFrameRate()
{
	return getFrameRate();
}

void GameGraphics::Window::setTargetFrameRate(int frameRate)
{
	SetTargetFPS(frameRate);
}

void GameGraphics::Window::beginDrawing(unsigned int color)
{
	BeginDrawing();
	ClearBackground(GetColor(color));
}

void GameGraphics::Window::endDrawing()
{
	EndDrawing();
}

void GameGraphics::Window::open()
{
	InitWindow(m_width, m_height, m_title);
}

void GameGraphics::Window::close()
{
	CloseWindow();
}