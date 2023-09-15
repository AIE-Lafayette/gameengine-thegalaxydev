#include "OBBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GameEngine/TransformComponent.h"
#include "Raylib/raylib.h"

#include <iostream>;

inline int clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;

	return value;
}

inline int min(int value1, int value2)
{
	return value1 < value2 ? value1 : value2;
}

inline int max(int value1, int value2)
{
	return value1 > value2 ? value1 : value2;
}

GamePhysics::OBBColliderComponent::OBBColliderComponent()
{
	m_size = GameMath::Vector3(1, 1, 1);
	setColliderType(OBB);
}

GamePhysics::OBBColliderComponent::OBBColliderComponent(GameMath::Vector3 size)
{
	setColliderType(OBB);
	m_size = size;
}

GamePhysics::OBBColliderComponent::OBBColliderComponent(GameMath::Vector2 size)
{
	setColliderType(OBB);
	m_size = GameMath::Vector3(size.x, size.y, 0);
}

GamePhysics::Collision* GamePhysics::OBBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position1 = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 position2 = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 direction = (position2 - position1);

	direction.x = clamp(direction.x, -getExtents().x, getExtents().x);
	direction.y = clamp(direction.y, -getExtents().y, getExtents().y);
	direction.z = clamp(direction.z, -getExtents().z, getExtents().z);

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

GamePhysics::Collision* GamePhysics::OBBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	return nullptr;
}

float* GamePhysics::OBBColliderComponent::projectOntoAxis(GameMath::Vector3* vertices, GameMath::Vector3 axis)
{

	float min = GameMath::Vector3::dotProduct(axis, vertices[0]);
	float max = min;

	for (int i = 1; i < 8; i++)
	{
		float projection = GameMath::Vector3::dotProduct(axis, vertices[i]);

		min = projection < min ? projection : min;
		max = projection > max ? projection : max;
	}

	return new float[2]{ min, max };
}

inline bool overlaps(float min1, float max1, float min2, float max2)
{
	return (min1 <= max2) && (min2 <= max1);
}

inline void sortArray(float* array, int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				float temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

float calculateOverlap(float minA, float maxA, float minB, float maxB) {
	float sortedPoints[4] = { minA, maxA, minB, maxB };

	sortArray(sortedPoints, 4);

	float overlap = sortedPoints[2] - sortedPoints[1];

	return (overlap > 0.0f) ? overlap : 0.0f;
}

GameMath::Vector3 calculateContactPoint(GameMath::Vector3* vertices, GameMath::Vector3* otherVertices, GameMath::Vector3 mtv)
{
	float minDistance = FLT_MAX;
	GameMath::Vector3 contactPoint = { 0,0,0 };

	for (int i = 0; i < 8; ++i) {
		GameMath::Vector3 vertex = vertices[i];

		for (int j = 0; j < 8; ++j) {
			GameMath::Vector3 otherVertex = otherVertices[j];

			float distance = (vertex - otherVertex).getMagnitude();

			if (distance < minDistance) {
				minDistance = distance;
				contactPoint = vertex;
			}
		}
	}

	return { contactPoint.x, contactPoint.y, 0 };

}

GameMath::Vector3 findNonZeroAxis(GameMath::Vector3* vertices) {
	for (int i = 0; i < 8; ++i) 
	{
		for (int j = i + 1; j < 8; ++j) 
		{
			GameMath::Vector3 temp = vertices[j] - vertices[i];
			if (temp.getMagnitude() > 1e-5) 
				return temp.getNormalized();
		}
	}
	return GameMath::Vector3(0, 0, 0); 
}

GamePhysics::Collision* GamePhysics::OBBColliderComponent::checkCollisionOBB(OBBColliderComponent* other)
{
	GameMath::Vector3* vertices = getVertices();
	GameMath::Vector3* otherVertices = other->getVertices();

	GameMath::Vector3 axes[3];
	GameMath::Vector3 otherAxes[3];

	axes[0] = findNonZeroAxis(vertices);
	axes[1] = findNonZeroAxis(vertices);
	axes[2] = findNonZeroAxis(vertices);

	otherAxes[0] = findNonZeroAxis(otherVertices);
	otherAxes[1] = findNonZeroAxis(otherVertices);
	otherAxes[2] = findNonZeroAxis(otherVertices);

	float minOverlap = FLT_MAX;
	GameMath::Vector3 collisionNormal = { 0,0,0 };

	for (int i = 0; i < 3; ++i) {
		GameMath::Vector3 axis = axes[i];
		auto proj1 = projectOntoAxis(vertices, axis);
		auto proj2 = projectOntoAxis(otherVertices, axis);

		if (!overlaps(proj1[0], proj1[1], proj2[0], proj2[1])) {
			return nullptr;
		}

		float overlap = calculateOverlap(proj1[0], proj1[1], proj2[0], proj2[1]);
		if (overlap < minOverlap) {
			minOverlap = overlap;
			collisionNormal = axis;
		}
	}

	for (int i = 0; i < 3; ++i) {
		GameMath::Vector3 axis = otherAxes[i];
		auto proj1 = projectOntoAxis(vertices, axis);
		auto proj2 = projectOntoAxis(otherVertices, axis);

		if (!overlaps(proj1[0], proj1[1], proj2[0], proj2[1])) {
			return nullptr;
		}

		float overlap = calculateOverlap(proj1[0], proj1[1], proj2[0], proj2[1]);
		if (overlap < minOverlap) {
			minOverlap = overlap;
			collisionNormal = axis;
		}
	}

	/*for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			GameMath::Vector3 axis = GameMath::Vector3::crossProduct(axes[i], otherAxes[j]).normalize();
			auto proj1 = projectOntoAxis(vertices, axis);
			auto proj2 = projectOntoAxis(otherVertices, axis);

			if (!overlaps(proj1[0], proj1[1], proj2[0], proj2[1])) {
				return nullptr;
			}

			float overlap = calculateOverlap(proj1[0], proj1[1], proj2[0], proj2[1]);
			if (overlap < minOverlap) {
				minOverlap = overlap;
				collisionNormal = axis;
			}
		}
	}*/

	GameMath::Vector3 mtv = collisionNormal * minOverlap;

	Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = mtv.getNormalized();
	collisionData->contactPoint = calculateContactPoint(vertices, otherVertices, mtv);
	collisionData->penetrationDistance = mtv.getMagnitude();

	return collisionData;
}

void GamePhysics::OBBColliderComponent::draw()
{
	if (!getIsDebug())
		return;

	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	Rectangle rectangle = { position.x - m_size.x / 2, position.y - m_size.y / 2, m_size.x, m_size.y };
	RAYLIB_H::DrawRectanglePro(rectangle, { 0 , 0 }, getOrientation().y, GetColor(getColor()));
}

GameMath::Vector3 GamePhysics::OBBColliderComponent::getCenter()
{
	return getOwner()->getTransform()->getGlobalPosition();
}

GameMath::Vector3 GamePhysics::OBBColliderComponent::getOrientation()
{
	return getOwner()->getTransform()->getLocalRotation();
}

float degToRad(float value)
{
	return value * PI / 180.0f;
}

GameMath::Vector3 rotateAroundAxis(GameMath::Vector3 point, GameMath::Vector3 axis, float angle) {
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	return (point * cosTheta) + (GameMath::Vector3::crossProduct(axis, point) * sinTheta) + (axis * GameMath::Vector3::dotProduct(axis, point) * (1 - cosTheta));
}

GameMath::Vector3* GamePhysics::OBBColliderComponent::getVertices()
{
	GameMath::Vector3 center = getCenter();
	GameMath::Vector3 orientation = getOrientation();

	GameMath::Vector3 extents = getExtents();

	GameMath::Vector3* vertices = new GameMath::Vector3[8];

	vertices[0] = GameMath::Vector3(extents.x, extents.y, extents.z);
	vertices[1] = GameMath::Vector3(extents.x, extents.y, -extents.z);
	vertices[2] = GameMath::Vector3(extents.x, -extents.y, extents.z);
	vertices[3] = GameMath::Vector3(extents.x, -extents.y, -extents.z);
	vertices[4] = GameMath::Vector3(-extents.x, extents.y, extents.z);
	vertices[5] = GameMath::Vector3(-extents.x, extents.y, -extents.z);
	vertices[6] = GameMath::Vector3(-extents.x, -extents.y, extents.z);
	vertices[7] = GameMath::Vector3(-extents.x, -extents.y, -extents.z);

	for (int i = 0; i < 8; ++i) {
		GameMath::Vector3 vertex = vertices[i];

		// Apply rotations around each axis
		vertex = rotateAroundAxis(vertex, GameMath::Vector3(1, 0, 0), orientation.x); 
		vertex = rotateAroundAxis(vertex, GameMath::Vector3(0, 1, 0), orientation.y);
		vertex = rotateAroundAxis(vertex, GameMath::Vector3(0, 0, 1), orientation.z);

		vertices[i] = vertex + center;
	}

	return vertices;
}

GameMath::Vector3 GamePhysics::OBBColliderComponent::getExtents()
{
	GameMath::Vector3 size = getSize();

	return GameMath::Vector3(size.x / 2, size.y / 2, size.z / 2);
}