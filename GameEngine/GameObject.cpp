#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include <GamePhysics/ColliderComponent.h>

GameEngine::GameObject::GameObject() 
{
	m_transform = addComponent<TransformComponent>();
}

void GameEngine::GameObject::start()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->start();
	}

	m_started = true;
	onStart();
}

void GameEngine::GameObject::update(double deltaTime)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->update(deltaTime);
	}

	onUpdate(deltaTime);
}

void GameEngine::GameObject::fixedUpdate()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->fixedUpdate();
	}

	onFixedUpdate();
}

void GameEngine::GameObject::draw()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->draw();
	}

	onDraw();
}

void GameEngine::GameObject::end()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->end();
	}

	onEnd();

	m_started = false;
}

void GameEngine::GameObject::addComponent(Component* component)
{
	component->setOwner(this);
	m_components.add(component);
}

void GameEngine::GameObject::setEnabled(bool value)
{
	if (!m_enabled && value)
		onEnable();
	else if (m_enabled && !value)
		onDisable();

	m_enabled = value;
}

void GameEngine::GameObject::onCollision(GamePhysics::Collision* collision)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->onCollision(collision);
	}
}