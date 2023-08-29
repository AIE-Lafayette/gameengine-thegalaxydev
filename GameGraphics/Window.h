#pragma once


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

		void beginDrawing(unsigned int color = 0x000000FF);
		void endDrawing();

		void close();

	private:
		int m_width;
		int m_height;
		const char* m_title;
	};
}

