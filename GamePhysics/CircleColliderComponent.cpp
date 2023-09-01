#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include "GameEngine/TransformComponent.h"

#include <Raylib/raylib.h>

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	float distance = (position1 - position2).getMagnitude();

	if (distance > getRadius() + other->getRadius())
		return nullptr;

	Collision* collisionData = new Collision();
	collisionData->collider = this;
	collisionData->normal = (position2 - position1).getNormalized();
	collisionData->penetration = getRadius() + other->getRadius() - distance;
}

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	return nullptr;
}


void GamePhysics::CircleColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::Vector3 newPos = { position.x, position.y, position.z };
	RAYLIB_H::DrawSphereWires(newPos, getRadius(), 32, 32, RAYLIB_H::GetColor(getColor()));
}
