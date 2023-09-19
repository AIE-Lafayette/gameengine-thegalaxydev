#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include "GameEngine/TransformComponent.h"


#include <Raylib/raylib.h>


inline int clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;

	return value;
}

GamePhysics::CircleColliderComponent::CircleColliderComponent(float radius)
{
	m_radius = radius;

	setColliderType(CIRCLE);
}

GamePhysics::CircleColliderComponent::CircleColliderComponent()
{
	m_radius = 1;

	setColliderType(CIRCLE);
}


GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	float distance = (position1 - position2).getMagnitude();

	if (distance > getRadius() + other->getRadius())
		return nullptr;

	GameMath::Vector3 direction = (position2 - position1).getNormalized();

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->contactPoint = position1 + direction * getRadius();
	collisionData->normal = direction;
	collisionData->penetrationDistance = getRadius() + other->getRadius() - distance;

	return collisionData;
}

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	Collision* collisionData = other->checkCollisionCircle(this);
	
	if (!collisionData)
		return nullptr;

	collisionData->collider = other;
	collisionData->normal = collisionData->normal * -1;
	return collisionData;
}


void GamePhysics::CircleColliderComponent::draw()
{
	if (!getIsDebug())
		return;

	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::Vector3 newPos = { position.x, position.y, position.z };
	RAYLIB_H::DrawSphereWires(newPos, getRadius(), 32, 32, RAYLIB_H::GetColor(getColor()));
}
