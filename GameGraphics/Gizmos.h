#pragma once

#include <GameMath/Vector2.h>
#include <GameMath/Vector4.h>
#include <GameGraphics/Color4.h>
#include <GameGraphics/Shader.h>

namespace GameGraphics
{
	class Gizmos
	{
	public:
		static void init();
		static void drawTriangle(GameMath::Vector2 p1, GameMath::Vector2 p2, GameMath::Vector2 p3, GameGraphics::Color4 color);

		static void drawTriangleLines(GameMath::Vector2 p1, GameMath::Vector2 p2, GameMath::Vector2 p3, GameGraphics::Color4 color);

		static void drawRectangle(GameMath::Vector2 position, float width, float height, float rotation, GameGraphics::Color4 color);
		static void drawRectangleLines(GameMath::Vector2 position, float width, float height, float rotation, GameGraphics::Color4 color);

		static void drawRectangle(GameMath::Vector2 position, float width, float height, GameGraphics::Color4 color);
		static void drawRectangleLines(GameMath::Vector2 position, float width, float height, GameGraphics::Color4 color);

		static void drawCircle(GameMath::Vector2 position, float radius, int slices, GameGraphics::Color4 color);

		static void drawCircleLines(GameMath::Vector2 position, float radius, int slices, GameGraphics::Color4 color);

		static void drawLine(GameMath::Vector2 p1, GameMath::Vector2 p2, GameGraphics::Color4 color);

		static Shader* getShader() { return m_shader; }

	private:
		static Shader* m_shader;
	};
}
