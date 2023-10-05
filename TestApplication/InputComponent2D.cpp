#include "InputComponent2D.h"

GameMath::Vector3 InputComponent2D::getMoveDirection()
{
	//int x = -IsKeyDown(KEY_A) + IsKeyDown(KEY_D);
	//int y = -IsKeyDown(KEY_W) + IsKeyDown(KEY_S);

	return GameMath::Vector3(0, 0, 0).getNormalized();
}