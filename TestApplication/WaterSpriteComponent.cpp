#include "WaterSpriteComponent.h"

void WaterSpriteComponent::update(double deltaTime)
{
	m_offset.x += deltaTime * m_OffsetVector.x;
	m_offset.y += deltaTime * m_OffsetVector.y;

	getShader()->setVec2("offset", m_offset);
}


