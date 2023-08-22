#pragma once

namespace GameEngine {
	class Engine
	{
	public:
		Engine() {}

		void run();

		static double getDeltaTime() { return m_deltaTime; }

		bool getApplicationShouldClose() { return m_applicationShouldClose; }
		void setApplicationShouldClose(bool value) { m_applicationShouldClose = value; }

	private:
		// functions
		void start();
		void update(double deltaTime);
		void draw();
		void end();

		// member variables
		static double m_deltaTime;
		bool m_applicationShouldClose = false;
	};
}


