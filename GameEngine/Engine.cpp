#include "Engine.h"
#include <chrono>
#include "GameGraphics/Window.h"

GameEngine::Scene* GameEngine::Engine::m_currentScene = nullptr;
double GameEngine::Engine::m_deltaTime = 0;

GameGraphics::Window window;

void GameEngine::Engine::run()
{
	start();

	double lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	double deltaTime = 0;
	double elapsedTime = 0;
	
	window = GameGraphics::Window(800, 600, "Game");
	window.open();
	window.setTargetFrameRate(60);


	while (!getApplicationShouldClose())
	{
		double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		m_deltaTime = deltaTime / 1000;

		update(m_deltaTime);

		elapsedTime += m_deltaTime;
		if (elapsedTime >= m_fixedTimeStep)
		{
			fixedUpdate();
			elapsedTime = 0;
		}

		window.beginDrawing();
		draw();
		window.endDrawing();
	}

	end();

	window.close();
}

void GameEngine::Engine::start()
{
	m_currentScene->start();
}

void GameEngine::Engine::update(double deltaTime)
{
	m_currentScene->update(deltaTime);
}

void GameEngine::Engine::fixedUpdate()
{
	m_currentScene->fixedUpdate();
}

void GameEngine::Engine::draw()
{
	m_currentScene->draw();
}

void GameEngine::Engine::end()
{
	m_currentScene->end();
}

bool GameEngine::Engine::getApplicationShouldClose()
{
	return window.getShouldClose();
}

void GameEngine::Engine::closeApplication()
{
	window.close();
}