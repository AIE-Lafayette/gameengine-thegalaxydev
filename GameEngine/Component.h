#pragma once
#include "GameObject.h"



namespace GameEngine
{
	class Component
	{
	public:
		Component() { m_enabled = true; }

		virtual void start() {}
		virtual void update(double deltaTime) {}
		virtual void fixedUpdate() {}
		virtual void draw() {}
		virtual void end() {}

		virtual void onEnable() {}
		virtual void onDisable() {}

		virtual void onCollision(GamePhysics::Collision* collision) {}

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool value);

		GameObject* getOwner() { return m_owner; }

	private:
		void setOwner(GameObject* gameObject) { m_owner = gameObject; }
		bool m_enabled = true;
		GameObject* m_owner = nullptr;

		friend GameObject;
	};

}

