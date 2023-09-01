#pragma once
#include "GameEngine/Component.h"
#include <GameMath/Vector3.h>

namespace GamePhysics
{
	class RigidBodyComponent;

	class CircleColliderComponent;
	class AABBColliderComponent;

	class ColliderComponent :
		public GameEngine::Component
	{	
	public:
		enum ColliderType
		{
			CIRCLE,
			AABB
		};

		ColliderComponent() {}

		void start() override;

		Collision* checkCollision(ColliderComponent* other);

		virtual Collision* checkCollisionCircle(CircleColliderComponent* other) = 0;
		virtual Collision* checkCollisionAABB(AABBColliderComponent* other) = 0;

		bool getIsTrigger() { return m_isTrigger; }
		void setIsTrigger(bool value) { m_isTrigger = value; }

		ColliderType getColliderType() { return m_collisionType; }
		void setColliderType(ColliderType value) { m_collisionType = value; }

		unsigned int getColor() { return m_color; }

		RigidBodyComponent * getRigidBody() { return m_rigidBody; }

		void onCollision(Collision* collision) override;

		void update(double deltaTime) override;

	private:
		ColliderType m_collisionType;

		bool m_isTrigger;

		unsigned int m_color = 0x00FF00FF;

		RigidBodyComponent* m_rigidBody;
	};

	struct Collision
	{
	public:
		ColliderComponent* collider;
		GameMath::Vector3 normal;
		float penetration;
	};
	
}

