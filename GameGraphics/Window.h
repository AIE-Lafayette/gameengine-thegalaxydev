#pragma once
#include <GameMath/Vector2.h>
#include <GameGraphics/Color4.h>

struct GLFWwindow;

namespace GameGraphics
{
	class Window
	{
	public:
		Window() {}
		Window(int width, int height, const char* title = "Window");

		int getWidth() { return m_width; }
		int getHeight() { return m_height; }
		const char* getTitle() { return m_title; }

		bool getShouldClose();

		int getFrameRate();
		void setTargetFrameRate(int targetFrameRate);

		void open();

		void beginDrawing(GameGraphics::Color4 color = {0,0,0,1});
		void endDrawing();

		void close();

		static GameMath::Vector2 convertToScreenPosition(GameMath::Vector2 position);
		static GameMath::Vector2 convertToWorldPosition(float x, float y);

		GLFWwindow* getWindowContext() { return m_window; }

	private:
		int m_width;
		int m_height;
		const char* m_title;
		GLFWwindow* m_window;
	};
}

