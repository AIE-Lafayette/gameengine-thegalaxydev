#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GameEngine/TransformComponent.h"
#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"

#include "GameEngine/Engine.h"
#include "GameEngine/Scene.h"


void GamePhysics::ColliderComponent::start()
{
	GameEngine::Engine::getCurrentScene()->addActiveCollider(this);

	m_rigidBody = getOwner()->getComponent<GamePhysics::RigidBodyComponent>();

	if (!m_rigidBody)
		m_rigidBody = getOwner()->addComponent<GamePhysics::RigidBodyComponent>();
}

GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(GamePhysics::ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
		return checkCollisionCircle((CircleColliderComponent*)other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);

	break;
	}

	return nullptr;
}

void GamePhysics::ColliderComponent::onCollision(Collision* collision)
{
	m_color = 0xFF0000FF;
}

void GamePhysics::ColliderComponent::update(double deltaTime)
{
	m_color = 0x00FF00FF;
}

