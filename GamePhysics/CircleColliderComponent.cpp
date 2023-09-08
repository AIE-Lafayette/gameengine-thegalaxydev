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


GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	float distance = (position1 - position2).getMagnitude();

	if (distance > getRadius() + other->getRadius())
		return nullptr;

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = (position2 - position1).getNormalized();
	collisionData->penetration = getRadius() + other->getRadius() - distance;
}

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 closestPoint = (position2 - position1).getNormalized();
	
	GameMath::Vector3 otherSize = other->getOwner()->getTransform()->getGlobalScale();

	closestPoint.x = clamp(closestPoint.x, position1.x - otherSize.x / 2, position1.x + otherSize.x / 2);
	closestPoint.y = clamp(closestPoint.y, position1.y - otherSize.y / 2, position1.y + otherSize.y / 2);
	closestPoint.z = clamp(closestPoint.z, position1.z - otherSize.z / 2, position1.z + otherSize.z / 2);

	float distance = (position2 - closestPoint).getMagnitude();

	if (distance > getRadius())
		return nullptr;

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = (closestPoint - position2).getNormalized();
	collisionData->penetration = getRadius() - distance;

	return collisionData;
}


void GamePhysics::CircleColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::Vector3 newPos = { position.x, position.y, position.z };
	RAYLIB_H::DrawSphereWires(newPos, getRadius(), 32, 32, RAYLIB_H::GetColor(getColor()));
}
