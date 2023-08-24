#pragma once
#include "GameObject.h"
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

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		void addGameObject(GameObject* gameObject);
		void removeGameObject(GameObject* gameObject);

	private:
		List<GameObject*> m_gameObjects;
		bool m_started;
	};
}


