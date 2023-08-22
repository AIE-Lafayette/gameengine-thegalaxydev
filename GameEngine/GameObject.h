#pragma once
#include "List.h"

namespace GameEngine
{
	class Component;


	class GameObject
	{
	public:
		GameObject();

		void start();
		void update(double deltaTime);
		void draw();
		void end();

		bool getStarted() { return m_started; }
		
		void addComponent(Component* component);

		template<typename T>
		T* addComponent();

		template<typename T>
		T* getComponent();

		/// <summary>
		/// returns nullptr if the variable can't ne cast as the type
		/// otherwise, returns a pointer to the variable of the desired cast type.
		/// dynamic_cast<type>(pointer name)
		/// </summary>

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		virtual bool onEnable() { return m_enabled; }
		virtual void onDisable(bool value) { m_enabled = true; }

	private:
		bool m_enabled;
		bool m_started;

		List<Component*> m_components;
	};
}
