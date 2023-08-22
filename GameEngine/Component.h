#pragma once
#include "GameObject.h"

namespace GameEngine
{
	class Component
	{
	public:
		Component() {}

		virtual void start() {}
		virtual void update(double deltaTime) {}
		virtual void draw() {}
		virtual void end() {}

		virtual void onEnable() {}
		virtual void onDisable() {}

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool value) { m_enabled = value; }

		GameObject* getOwner() { return m_owner; }

	private:
		void setOwner(GameObject* gameObject) { m_owner = gameObject; }
		bool m_enabled;
		GameObject* m_owner = nullptr;

		friend GameObject;
	};

}

