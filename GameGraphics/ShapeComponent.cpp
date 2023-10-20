#include "ShapeComponent.h"
#include "GameGraphics/Color4.h"
#include "GameGraphics/Gizmos.h"

void GameGraphics::ShapeComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 scale = getOwner()->getTransform()->getGlobalScale();
	GameMath::Vector3 rotation = getOwner()->getTransform()->getLocalRotation();


	if (m_shapeType == CIRCLE)
		GameGraphics::Gizmos::drawCircle({ position.x ,position.y }, scale.x, 50, getColor4());
	else if (m_shapeType == BOX)
		GameGraphics::Gizmos::drawRectangle({ position.x ,position.y }, scale.x, scale.y, rotation.z, getColor4());

}