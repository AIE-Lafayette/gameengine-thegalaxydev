#pragma once

#include <GameMath/Vector2.h>

namespace GameEngine
{
	enum Key
	{
		KEY_A = 65,
		KEY_B = 66,
		KEY_C = 67,
		KEY_D = 68,
		KEY_E = 69,
		KEY_F = 70,
		KEY_G = 71,
		KEY_H = 72,
		KEY_I = 73,
		KEY_J = 74,
		KEY_K = 75,
		KEY_L = 76,
		KEY_M = 77,
		KEY_N = 78,
		KEY_O = 79,
		KEY_P = 80,
		KEY_Q = 81,
		KEY_R = 82,
		KEY_S = 83,
		KEY_T = 84,
		KEY_U = 85,
		KEY_V = 86,
		KEY_W = 87,
		KEY_X = 88,
		KEY_Y = 89,
		KEY_Z = 90,

		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_4 = 52,
		KEY_5 = 53,
		KEY_6 = 54,
		KEY_7 = 55,
		KEY_8 = 56,
		KEY_9 = 57,

		KEY_RETURN = 257,
		KEY_ESCAPE = 256,
		KEY_BACKSPACE = 259,
		KEY_TAB = 258,
		KEY_SPACE = 32,

		KEY_LEFTSHIFT = 340,
		KEY_LEFTCONTROL = 341,
		KEY_LEFTALT = 342,

		KEY_RIGHTSHIFT = 344,
		KEY_RIGHTCONTROL = 345,
		KEY_RIGHTALT = 346,

		KEY_EQUAL = 61,
		KEY_MINUS = 45,
		KEY_LEFTBRACKET = 91,
		KEY_RIGHTBRACKET = 93,
		KEY_SEMICOLON = 59,
		KEY_APOSTROPHE = 39,
		KEY_COMMA = 44,
		KEY_PERIOD = 46,
		KEY_SLASH = 47,
		KEY_BACKSLASH = 92,
		KEY_GRAVEACCENT = 96,

		KEY_UP = 265,
		KEY_DOWN = 264,
		KEY_LEFT = 263,
		KEY_RIGHT = 262,

		KEY_F1 = 290,
		KEY_F2 = 291,
		KEY_F3 = 292,
		KEY_F4 = 293,
		KEY_F5 = 294,
		KEY_F6 = 295,
		KEY_F7 = 296,
		KEY_F8 = 297,
		KEY_F9 = 298,
		KEY_F10 = 299,
		KEY_F11 = 300,
		KEY_F12 = 301,

		KEY_INSERT = 260,
		KEY_DELETE = 261,
		KEY_HOME = 268,
		KEY_END = 269,

		KEY_PAGEUP = 266,
		KEY_PAGEDOWN = 267
	};

	enum Mouse
	{
		MOUSEBUTTON_1 = 0,
		MOUSEBUTTON_2 = 1,
		MOUSEBUTTON_3 = 2,

		MOUSE_SCROLL = 3
	};

	static class Input
	{
	public:
		static bool isKeyDown(int keycode);
		static bool isKeyUp(int keycode);

		static bool setExitKey(int keycode);

		static bool isMouseButtonDown(int button);
		static bool isMouseButtonUp(int button);

		static GameMath::Vector2 getMousePosition();
		static int getMouseX();
		static int getMouseY();

		static void setMousePosition(GameMath::Vector2 position);

		float getMouseWheelMove();
	};
}

