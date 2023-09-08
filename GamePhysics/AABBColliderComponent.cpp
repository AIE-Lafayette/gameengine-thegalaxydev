#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
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

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 closestPoint = (position2 - position1).getNormalized();

	closestPoint.x = clamp(closestPoint.x, position1.x - m_size.x / 2, position1.x + m_size.x / 2);
	closestPoint.y = clamp(closestPoint.y, position1.y - m_size.y / 2, position1.y + m_size.y / 2);
	closestPoint.z = clamp(closestPoint.z, position1.z - m_size.z / 2, position1.z + m_size.z / 2);

	float distance = (position2 - closestPoint).getMagnitude();

	if (distance > other->getRadius())
		return nullptr;

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = (position2 - closestPoint).getNormalized();
	collisionData->penetration = other->getRadius() - distance;

	return collisionData;
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	bool isColliding = getRight() > other->getLeft() &&
		getLeft() < other->getRight() &&
		getUp() > other->getDown() &&
		getDown() < other->getUp() &&
		getFront() > other->getBack() &&
		getBack() < other->getFront();

	if (!isColliding)
		return nullptr;

	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = (position2 - position1).getNormalized();
	collisionData->penetration = 0;

	return collisionData;
}

float GamePhysics::AABBColliderComponent::getRight()
{
	return getOwner()->getTransform()->getGlobalPosition().x + m_size.x / 2;
}

float GamePhysics::AABBColliderComponent::getUp()
{
	return getOwner()->getTransform()->getGlobalPosition().y + m_size.y / 2;
}

float GamePhysics::AABBColliderComponent::getFront()
{
	return getOwner()->getTransform()->getGlobalPosition().z + m_size.z / 2;
}

float GamePhysics::AABBColliderComponent::getLeft()
{
	return getOwner()->getTransform()->getGlobalPosition().x - m_size.x / 2;
}

float GamePhysics::AABBColliderComponent::getDown()
{
	return getOwner()->getTransform()->getGlobalPosition().y - m_size.y / 2;
}

float GamePhysics::AABBColliderComponent::getBack()
{
	return getOwner()->getTransform()->getGlobalPosition().z - m_size.z / 2;
}

void GamePhysics::AABBColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
	RAYLIB_H Vector3 newPos = { position.x , position.y, position.z};

	RAYLIB_H::DrawCubeWires(newPos, m_size.x, m_size.y, m_size.z, RAYLIB_H::GetColor(getColor()));
}