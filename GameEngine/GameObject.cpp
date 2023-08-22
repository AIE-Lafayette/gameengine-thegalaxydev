#include "GameObject.h"
#include "Component.h"

GameEngine::GameObject::GameObject() 
{

}

void GameEngine::GameObject::start()
{
	for (Component* component : m_components)
	{
		component->start();
	}
}

void GameEngine::GameObject::update(double deltaTime)
{
	for (Component* component : m_components)
	{
		component->update(deltaTime);
	}
}

void GameEngine::GameObject::draw()
{
	for (Component* component : m_components)
	{
		component->draw();
	}
}

void GameEngine::GameObject::end()
{
	for (Component* component : m_components)
	{
		component->end();
	}
}

void GameEngine::GameObject::addComponent(Component* component)
{
	m_components.add(component);
}

template<typename T>
T* GameEngine::GameObject::addComponent()
{
	T* component = new T();
	
	m_components.add(component);

	return component;
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