#include "Scene.h"

void GameEngine::Scene::start()
{

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->getEnabled())
			gameObject->start();
	}

	m_started = true;
	onStart();
}

void GameEngine::Scene::update(double deltaTime)
{

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->getEnabled())
		{
			if (!gameObject->getStarted())
				gameObject->start();

			gameObject->update(deltaTime);
		}
	}
	

	onUpdate(deltaTime);
}

void GameEngine::Scene::draw()
{

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->getEnabled())
			gameObject->draw();
	}
	

	onDraw();
}

void GameEngine::Scene::end()
{

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->getEnabled())
			gameObject->end();
	}
	
	onEnd();
	m_started = false;
}

void GameEngine::Scene::addGameObject(GameObject* gameObject)
{
	m_gameObjects.add(gameObject);
}

void GameEngine::Scene::removeGameObject(GameObject* gameObject)
{
	m_gameObjects.remove(gameObject);
}