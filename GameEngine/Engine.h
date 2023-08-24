#pragma once
#include "Scene.h"

namespace GameEngine {
	class Engine
	{
	public:
		Engine() {}

		void run();

		static void setCurrentScene(Scene* scene) { m_currentScene = scene; }
		static Scene* getCurrentScene() { return m_currentScene; }

		static double getDeltaTime() { return m_deltaTime; }

		bool getApplicationShouldClose();
		void closeApplication();

		void addScene(Scene* scene);
		void removeScene(Scene* scene);

	private:
		// functions
		void start();
		void update(double deltaTime);
		void draw();
		void end();

		// member variables
		static double m_deltaTime;
		static Scene* m_currentScene;
	};
}


