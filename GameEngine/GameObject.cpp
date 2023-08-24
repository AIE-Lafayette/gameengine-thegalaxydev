#include "GameObject.h"
#include "Component.h"

GameEngine::GameObject::GameObject() 
{

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

template<typename T>
T* GameEngine::GameObject::addComponent()
{
	T* component = new T();

	component->setOwner(this);
	m_components.add(component);
	

	return (T*)component;
}

template<typename T>
T* GameEngine::GameObject::getComponent()
{
	for (Component* component : m_components)
	{
		if (dynamic_cast<T*>(component))
			return component;
	}

	return nullptr;
}

void GameEngine::GameObject::setEnabled(bool value)
{
	if (!m_enabled && value)
		onEnable();
	else if (m_enabled && !value)
		onDisable();

	m_enabled = value;
}