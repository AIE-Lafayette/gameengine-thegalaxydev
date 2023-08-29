#include "RigidBodyComponent.h"
#include "TransformComponent.h"

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector3 force)
{
	setVelocity3D(getVelocity3D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	setVelocity2D(getVelocity2D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(float x, float y, float z)
{
	setVelocity3D(getVelocity3D() + GameMath::Vector3(x, y, z) / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(float x, float y)
{
	setVelocity2D(getVelocity2D() + GameMath::Vector2(x, y) / getMass());
}

void GamePhysics::RigidBodyComponent::applyForceToGameObject(RigidBodyComponent* other, GameMath::Vector3 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyForceToGameObject(RigidBodyComponent* other, GameMath::Vector2 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::update(double deltaTime)
{
	applyForce(GameMath::Vector3(0, getGravity() * getMass(), 0));
	setVelocity3D(getVelocity3D() + getAcceleration3D() * deltaTime);
	
	GameMath::Vector3 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + getVelocity3D() * deltaTime);
}