#pragma once
#include "List.h"
#include <GameMath/Vector2.h>

namespace GamePhysics
{
	struct Collision;
}

namespace GameEngine
{
	class Component;
	class TransformComponent;

	class GameObject
	{
	public:
		GameObject();

		/// <summary>
		/// Called at the start before the first update only once.
		/// </summary>
		void start();

		/// <summary>
		/// Called every frame.
		/// </summary>
		/// <param name="deltaTime">The time passed between each frame in seconds.</param>
		void update(double deltaTime);


		/// <summary>
		/// Called every fixed frame for physics calculations.
		/// </summary>
		void fixedUpdate();

		/// <summary>
		/// Called every frame after update.
		/// </summary>
		void draw();

		/// <summary>
		/// Called after the last draw call.
		/// </summary>
		void end();

		/// <returns>Whether the game object has started.</returns>
		bool getStarted() { return m_started; }

		TransformComponent* getTransform() { return m_transform; }

		/// <returns>Whether the game object is enabled.</returns>
		bool getEnabled() { return m_enabled; }

		/// <summary>
		/// Sets the enabled status of the game object. Will call onEnable() and onDisable() accordingly.
		/// </summary>
		/// <param name="value">The boolean to set.</param>
		void setEnabled(bool value);
		
		/// <summary>
		/// Adds a component to the game object given a pre-existing component. 
		/// </summary>
		/// <param name="component">The component to provide.</param>
		void addComponent(Component* component);
		
		/// <summary>
		/// Adds a component to the game object given a type.
		/// </summary>
		/// <typeparam name="T">The type of component to add,</typeparam>
		/// <returns>The component added.</returns>
		template<typename T>
		T* addComponent();

		/// <summary>
		/// Returns a component based on a type provided.
		/// </summary>
		/// <typeparam name="T">The type of component to return.</typeparam>
		/// <returns>The component if found.</returns>
		template<typename T>
		T* getComponent();

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onFixedUpdate() {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		virtual void onEnable() {}
		virtual void onDisable() {}

		virtual void onCollision(GamePhysics::Collision* collision);

	private:
		bool m_enabled = true;
		bool m_started;

		TransformComponent* m_transform;

		List<Component*> m_components;
	};
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
	T* result = nullptr;
	for (Component* component : m_components)
	{
		if (result = dynamic_cast<T*>(component))
			break;
	}

	return result;
}