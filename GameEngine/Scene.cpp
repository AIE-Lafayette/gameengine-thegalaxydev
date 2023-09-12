#include "Scene.h"
#include "GameObject.h"
#include "GamePhysics/ColliderComponent.h"
#include "GamePhysics/RigidBodyComponent.h"

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

void GameEngine::Scene::fixedUpdate()
{

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->getEnabled())
		{
			if (!gameObject->getStarted())
				gameObject->start();

			gameObject->fixedUpdate();
		}
	}

	onFixedUpdate();

	for (auto iterator1 = m_activeColliders.begin(); iterator1 != m_activeColliders.end(); iterator1++)
	{
		for (auto iterator2 = iterator1; iterator2 != m_activeColliders.end(); iterator2++)
		{
			GamePhysics::ColliderComponent* collider1 = *iterator1;
			GamePhysics::ColliderComponent* collider2 = *iterator2;
				
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
				collider1->getRigidBody()->resolveCollision(collisionData1);

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