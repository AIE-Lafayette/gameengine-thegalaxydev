#pragma once
#include "GameObject.h"

namespace GamePhysics
{
	class ColliderComponent;
}

namespace GameEngine
{
	class Scene
	{
	public:
		Scene() { m_gameObjects = List<GameObject*>(); }

		void start();
		void update(double deltaTime);
		void draw();
		void end();
		void fixedUpdate();
		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onDraw() {}
		virtual void onFixedUpdate() {}
		virtual void onEnd() {}

		void addGameObject(GameObject* gameObject);
		void removeGameObject(GameObject* gameObject);

		void addActiveCollider(GamePhysics::ColliderComponent* activeCollider);
		void removeActiveCollider(GamePhysics::ColliderComponent* activeCollider);

	private:
		List<GameObject*> m_gameObjects;
		bool m_started;
		List<GamePhysics::ColliderComponent*> m_activeColliders;
	};
}


