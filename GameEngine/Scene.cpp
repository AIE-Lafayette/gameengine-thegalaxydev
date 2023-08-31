#include "Scene.h"
#include "GameObject.h"
#include "GamePhysics/ColliderComponent.h"

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

	for (GamePhysics::ColliderComponent* collider1 : m_activeColliders)
	{
		for (GamePhysics::ColliderComponent* collider2 : m_activeColliders)
		{
			if (collider1 == collider2)
				continue;
			
			if (!collider2->getOwner()->getEnabled())
				continue;

			if (!collider1->getOwner()->getEnabled())
				continue;

			GamePhysics::Collision* collisionData1 = nullptr;
			GamePhysics::Collision* collisionData2 = new GamePhysics::Collision();

			if (collisionData1 = collider1->checkCollision(collider2))
			{
				collider1->getOwner()->onCollision(collisionData1);

				collisionData2->collider = collider1;  
				collisionData2->normal = collisionData1->normal * -1.0f;

				collider2->getOwner()->onCollision(collisionData2);
			}
		}
	}
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

void GameEngine::Scene::addActiveCollider(GamePhysics::ColliderComponent* activeCollider)
{
	m_activeColliders.add(activeCollider);
}

void GameEngine::Scene::removeActiveCollider(GamePhysics::ColliderComponent* activeCollider)
{
	m_activeColliders.remove(activeCollider);
}