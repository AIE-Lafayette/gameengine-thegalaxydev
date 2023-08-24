#include "ShapeComponent.h"
#include <Raylib/raylib.h>

void GameGraphics::ShapeComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	Color color = RAYLIB_H::GetColor(m_color);

	GameMath::Vector3 scale = getOwner()->getTransform()->getGlobalScale();

	if (m_shapeType == CIRCLE)
		RAYLIB_H::DrawEllipse(position.x, position.y, scale.x, scale.y, color);
	else if (m_shapeType == BOX)
		RAYLIB_H::DrawRectangle(position.x - scale.x / 2, position.y - scale.y / 2, scale.x, scale.y, color);

}