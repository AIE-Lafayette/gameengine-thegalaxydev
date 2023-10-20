#pragma once
#include <GameMath/Vector4.h>

namespace GameGraphics
{
	struct Color4
	{
	public:
		Color4();
		Color4(float r, float g, float b, float a);

		float getR() { return m_r; }
		float getG() { return m_g; }
		float getB() { return m_b; }
		float getA() { return m_a; }

		static GameGraphics::Color4 getColorRGBA(float r, float g, float b, float a);
		static GameGraphics::Color4 getColorRGBA(GameMath::Vector4 rgba);

		static GameGraphics::Color4 getColorRGB(float r, float g, float b);

		static GameGraphics::Color4 getColorHex(unsigned int color);

		static GameGraphics::Color4 getColorHSVA(float h, float s, float v, float a);
		static GameGraphics::Color4 getColorHSVA(GameMath::Vector4 hsva);

		static GameGraphics::Color4 getColorHSV(float h, float s, float v);


		unsigned int toHex();
		GameMath::Vector4 toRGBA();

	private:
		float m_r;
		float m_g;
		float m_b;
		float m_a;
	};


}