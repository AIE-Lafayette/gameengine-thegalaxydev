#include "Bumper.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/ColliderComponent.h"
#include "GamePhysics/AABBColliderComponent.h"
#include "GamePhysics/RigidBodyComponent.h"

Bumper::Bumper()
{
	m_shapeComponent = addComponent<GameGraphics::ShapeComponent>();
	m_shapeComponent->setShapeType(GameGraphics::CUBE);

	m_collider = addComponent<GamePhysics::AABBColliderComponent>();
}

void Bumper::onCollision(GamePhysics::Collision* other)
{
	other->collider->getRigidBody()->applyForceToGameObject(m_collider->getRigidBody(), other->normal * 200);
}

void Bumper::onStart()
{
	GamePhysics::RigidBodyComponent* rigidBody = m_collider->getRigidBody();
	rigidBody->setIsKinematic(true);
	rigidBody->setGravity(0);
}

void Bumper::onUpdate(double deltaTime)
{
}

void Bumper::onFixedUpdate()
{
}

void Bumper::onDraw()
{
}
