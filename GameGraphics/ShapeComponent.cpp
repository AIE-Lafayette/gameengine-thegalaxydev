#include "ShapeComponent.h"
#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>

void GameGraphics::ShapeComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	Color color = RAYLIB_H::GetColor(m_color);

	GameMath::Vector3 scale = getOwner()->getTransform()->getGlobalScale();
	GameMath::Vector3 rotation = getOwner()->getTransform()->getLocalRotation();

	RAYLIB_H::Vector3 newPos = { position.x, position.y, position.z };
	RAYLIB_H::Vector3 newScale = { scale.x, scale.y, scale.z };
	RAYLIB_H::Vector3 newRotation = { rotation.x, rotation.y, rotation.z };

	if (m_shapeType == CIRCLE)
		RAYLIB_H::DrawEllipse(position.x, position.y, scale.x, scale.y, color);
	else if (m_shapeType == BOX)
	{
		Rectangle rectangle = { position.x - scale.x / 2, position.y - scale.y / 2, scale.x, scale.y };
		RAYLIB_H::DrawRectanglePro(rectangle, {0 , 0}, newRotation.y, color);
	}
	else if (m_shapeType == SPHERE)
		RAYLIB_H::DrawSphere(newPos, newScale.x, color);
	else if (m_shapeType == CUBE)
		RAYLIB_H::DrawCube(newPos, newScale.x, newScale.y, newScale.z, RAYLIB_H::GetColor(getColor()));

}