#include "InputComponent2D.h"
#include <Raylib/raylib.h>

GameMath::Vector3 InputComponent2D::getMoveDirection()
{
	int x = -IsKeyDown(KEY_A) + IsKeyDown(KEY_D);
	int y = -IsKeyDown(KEY_W) + IsKeyDown(KEY_S);

	return GameMath::Vector3(x, y, 0).getNormalized();
}