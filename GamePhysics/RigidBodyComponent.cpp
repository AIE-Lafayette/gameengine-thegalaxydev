#include "RigidBodyComponent.h"
#include "GameEngine/TransformComponent.h"
#include "ColliderComponent.h"
#include "GameEngine/Engine.h"

#include <iostream>

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector3 force)
{
	if (getIsKinematic())
		return;

	setVelocity3D(getVelocity3D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	if (getIsKinematic())
		return;

	setVelocity2D(getVelocity2D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(float x, float y, float z)
{
	if (getIsKinematic())
		return;

	setVelocity3D(getVelocity3D() + GameMath::Vector3(x, y, z) / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(float x, float y)
{
	if (getIsKinematic())
		return;

	setVelocity2D(getVelocity2D() + GameMath::Vector2(x, y) / getMass());
}
void GamePhysics::RigidBodyComponent::applyForceToGameObject(RigidBodyComponent* other, GameMath::Vector2 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyForceToGameObject(RigidBodyComponent* other, GameMath::Vector3 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyContactForce(GamePhysics::Collision* other)
{
	float mass = getMass();
	float massOther = other->collider->getRigidBody()->getMass();

	float displacement1 = 1;

	float penetrationDistance = other->penetrationDistance;

	if (massOther != INFINITY && !getIsKinematic())
		displacement1 = massOther / (mass + massOther);

	if (!getIsKinematic())
	{
		GameMath::Vector3 position = getOwner()->getTransform()->getLocalPosition();
		getOwner()->getTransform()->setLocalPosition(position + other->normal * -penetrationDistance);
		//applyForceToGameObject(other->collider->getRigidBody(), other->normal * displacement1 * penetrationDistance);
	}
}
void GamePhysics::RigidBodyComponent::applyFrictionForce(GamePhysics::Collision* other)
{
    float normalForceMagnitude = other->normal.getMagnitude(); 

    float averageStaticCoefficient = (getStaticFrictionCoefficient() + other->collider->getRigidBody()->getStaticFrictionCoefficient()) / 2;
    float averageDynamicCoefficient = (getDynamicFrictionCoefficient() + other->collider->getRigidBody()->getDynamicFrictionCoefficient()) / 2;

    GameMath::Vector3 staticFrictionForce = other->normal * (averageStaticCoefficient * normalForceMagnitude);
    GameMath::Vector3 velocity = getVelocity3D();

    if (velocity.getMagnitude() < staticFrictionForce.getMagnitude())
    {
        applyForce(velocity * -1);
    }
    else
    {
        GameMath::Vector3 dynamicFrictionForce = other->normal * (averageDynamicCoefficient * normalForceMagnitude);
        GameMath::Vector3 frictionDirection = velocity.getNormalized() * -1;

        if (velocity.getMagnitude() > 0)
        {
            applyForce(frictionDirection * dynamicFrictionForce.getMagnitude());
        }
    }
}


void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	applyFrictionForce(collisionData);
	applyContactForce(collisionData);
	GamePhysics::RigidBodyComponent* current = this;
	GamePhysics::RigidBodyComponent* other = collisionData->collider->getRigidBody();
	float averageElasticity = (getElasticity() + collisionData->collider->getRigidBody()->getElasticity()) / 2;

	GameMath::Vector3 velocity = getVelocity3D();
	GameMath::Vector3 otherVelocity = other->getVelocity3D();

	GameMath::Vector3 normal = collisionData->normal;
	float mass = getMass();
	
	if (mass == 0)
		mass = 10e-12;

	float otherMass = other->getMass();

	if (otherMass == 0)
		otherMass = 10e-12;

	float dotProduct = GameMath::Vector3::dotProduct(velocity - otherVelocity, normal);
	float normalDotProduct = GameMath::Vector3::dotProduct(normal, normal * (1 / mass + 1 / otherMass));
	// j = (-(1 + e) * dot(vA - vB, n)) / (dot(n,n * (1/mA + 1/mB)))
	if (normalDotProduct == 0)
		return;

	float impulse = (-(1 + averageElasticity) * dotProduct) / normalDotProduct;

	applyForceToGameObject(other, normal * -impulse);
}

void GamePhysics::RigidBodyComponent::update(double deltaTime)
{
}

void GamePhysics::RigidBodyComponent::fixedUpdate()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + getVelocity3D() * GameEngine::Engine::getFixedDeltaTime());

	applyForce(GameMath::Vector3(0, getGravity(), 0));
}

float GamePhysics::RigidBodyComponent::getMass()
{
	if (getIsKinematic())
		return INFINITY;

	return m_mass;
}