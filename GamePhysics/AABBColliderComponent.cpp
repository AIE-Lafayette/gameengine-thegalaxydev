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

GamePhysics::AABBColliderComponent::AABBColliderComponent()
{
	m_size = GameMath::Vector3(0, 0, 0);

	setColliderType(AABB);
}

GamePhysics::AABBColliderComponent::AABBColliderComponent(GameMath::Vector3 size)
{
	m_size = size;

	setColliderType(AABB);
}

GamePhysics::AABBColliderComponent::AABBColliderComponent(GameMath::Vector2 size)
{
	m_size = GameMath::Vector3(size.x, size.y, 0);

	setColliderType(AABB);
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 direction = (position2 - position1);

	direction.x = clamp(direction.x, -m_size.x / 2, m_size.x / 2);
	direction.y = clamp(direction.y, -m_size.y / 2, m_size.y / 2);
	direction.z = clamp(direction.z, -m_size.z / 2, m_size.z / 2);

	GameMath::Vector3 closestPoint = position1 + direction;
	float distance = (position2 - closestPoint).getMagnitude();


	direction.normalize();
	float radius = other->getRadius();
	if (distance > radius)
		return nullptr;

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = (position2 - closestPoint).getNormalized();
	collisionData->contactPoint = closestPoint;
	collisionData->penetrationDistance = radius - distance;

	return collisionData;
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	float right = getRight(); float otherRight = other->getRight();
	float left = getLeft(); float otherLeft = other->getLeft();
	float up = getUp(); float otherUp = other->getUp();
	float down = getDown(); float otherDown = other->getDown();
	float front = getFront(); float otherFront = other->getFront();
	float back = getBack(); float otherBack = other->getBack();

	bool isColliding = right >= otherLeft && 
		left <= otherRight && 
		up >= otherDown && 
		down <= otherUp && 
		front >= otherBack && 
		back <= otherFront;

	if (!isColliding)
		return nullptr;

	GameMath::Vector3 otherToAABB = other->getOwner()->getTransform()->getGlobalPosition() - getOwner()->getTransform()->getGlobalPosition();

	otherToAABB.x = clamp(otherToAABB.x, -m_size.x / 2, m_size.x / 2);
	otherToAABB.y = clamp(otherToAABB.y, -m_size.y / 2, m_size.y / 2);
	otherToAABB.z = clamp(otherToAABB.z, -m_size.z / 2, m_size.z / 2);

	GameMath::Vector3 closestPoint = getOwner()->getTransform()->getGlobalPosition() + otherToAABB;
	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->contactPoint = closestPoint;
	collisionData->normal = getPenetrationVector(other).getNormalized();
	collisionData->penetrationDistance = getPenetrationVector(other).getMagnitude();

	return collisionData;
}

float GamePhysics::AABBColliderComponent::getRight()
{
	return getOwner()->getTransform()->getGlobalPosition().x + m_size.x / 2;
}

float GamePhysics::AABBColliderComponent::getLeft()
{
	return getOwner()->getTransform()->getGlobalPosition().x - m_size.x / 2;
}

float GamePhysics::AABBColliderComponent::getFront()
{
	return getOwner()->getTransform()->getGlobalPosition().z + m_size.z / 2;
}

float GamePhysics::AABBColliderComponent::getBack()
{
	return getOwner()->getTransform()->getGlobalPosition().z - m_size.z / 2;
}

float GamePhysics::AABBColliderComponent::getDown()
{
	return getOwner()->getTransform()->getGlobalPosition().y - m_size.y / 2;
}


float GamePhysics::AABBColliderComponent::getUp()
{
	return getOwner()->getTransform()->getGlobalPosition().y + m_size.y / 2;
}

void GamePhysics::AABBColliderComponent::draw()
{
	if (!getIsDebug())
		return;

	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
	RAYLIB_H Vector3 newPos = { position.x , position.y, position.z};

	RAYLIB_H::DrawCubeWires(newPos, m_size.x, m_size.y, m_size.z, RAYLIB_H::GetColor(getColor()));
}

GameMath::Vector3 GamePhysics::AABBColliderComponent::getPenetrationVector(AABBColliderComponent* other)
{
	float smallestPenetration = abs(getRight() - other->getLeft());
	GameMath::Vector3 normalFace = GameMath::Vector3(1, 0, 0);

	if (abs(getLeft() - other->getRight()) <= smallestPenetration)
	{
		smallestPenetration = abs(getLeft() - other->getRight());
		normalFace = GameMath::Vector3(-1, 0, 0);
	}

	if (abs(getUp() - other->getDown()) <= smallestPenetration)
	{
		smallestPenetration = abs(getUp() - other->getDown());
		normalFace = GameMath::Vector3(0, 1, 0);
	}

	if (abs(getDown() - other->getUp()) <= smallestPenetration)
	{
		smallestPenetration = abs(getDown() - other->getUp());
		normalFace = GameMath::Vector3(0, -1, 0);
	}

	//if (abs(getFront() - other->getBack()) <= smallestPenetration)
	//{
	//	smallestPenetration = abs(getFront() - other->getBack());
	//	normalFace = GameMath::Vector3(0, 0, 1);
	//}

	//if (abs(getBack() - other->getFront()) <= smallestPenetration)
	//{		
	//	smallestPenetration = abs(getBack() - other->getFront());
	//	normalFace = GameMath::Vector3(0, 0, -1);
	//}

	return normalFace * smallestPenetration;
}