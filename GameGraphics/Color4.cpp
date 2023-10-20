#include "Color4.h"
GameGraphics::Color4::Color4()
{
	m_r = 1.0f;
	m_g = 1.0f;
	m_b = 1.0f;
	m_a = 1.0f;
}

GameGraphics::Color4::Color4(float r, float g, float b, float a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

GameGraphics::Color4 GameGraphics::Color4::getColorRGBA(float r, float g, float b, float a)
{
	return Color4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

GameGraphics::Color4 GameGraphics::Color4::getColorRGBA(GameMath::Vector4 rgba)
{
	return getColorRGBA(rgba.x, rgba.y, rgba.z, rgba.w);
}


GameGraphics::Color4 GameGraphics::Color4::getColorRGB(float r, float g, float b)
{
	return Color4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

GameGraphics::Color4 GameGraphics::Color4::getColorHex(unsigned int color)
{
	float r = (color >> 24) & 0xFF;
	float g = (color >> 16) & 0xFF;
	float b = (color >> 8) & 0xFF;
	float a = color & 0xFF;

	return Color4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

GameGraphics::Color4 GameGraphics::Color4::getColorHSVA(float h, float s, float v, float a)
{
	h = h / 255;
	s = s / 255;
	v = v / 255;
	a = a / 255;	

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	if (s <= 0.0f) 
	{     
		r = v;
		g = v;
		b = v;

		return GameGraphics::Color4(r,g,b,a);
	}

	float hh = h;
	if (hh >= 360.0f)
		hh = 0.0f;

	hh /= 60.0f;

	int i = (int)hh;
	float ff = hh - i;

	float p = v * (1.0f - s);
	float q = v * (1.0f - (s * ff));
	float t = v * (1.0f - (s * (1.0f - ff)));

	switch (i)
	{
	case 0:
		r = v;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = v;
		b = p;
		break;
	case 2:
		r = p;
		g = v;
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = v;
		break;
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	case 5:
	default:
		r = v;
		g = p;
		b = q;
		break;
	}

	return GameGraphics::Color4(r, g, b, a);
}

GameGraphics::Color4 GameGraphics::Color4::getColorHSVA(GameMath::Vector4 hsva)
{
	return getColorHSVA(hsva.x, hsva.y, hsva.z, hsva.w);
}

GameGraphics::Color4 GameGraphics::Color4::getColorHSV(float h, float s, float v)
{
	return getColorHSVA(h, s, v, 255.0f);
}

unsigned int GameGraphics::Color4::toHex()
{
	unsigned int r = (unsigned int)(m_r * 255.0f);
	unsigned int g = (unsigned int)(m_g * 255.0f);
	unsigned int b = (unsigned int)(m_b * 255.0f);
	unsigned int a = (unsigned int)(m_a * 255.0f);

	return (r << 24) | (g << 16) | (b << 8) | a;
}

GameMath::Vector4 GameGraphics::Color4::toRGBA()
{
	return GameMath::Vector4(m_r, m_g, m_b, m_a);
}