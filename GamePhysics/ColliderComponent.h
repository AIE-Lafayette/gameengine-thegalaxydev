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
			AABB,
		};

		ColliderComponent() {}

		void start() override;

		Collision* checkCollision(ColliderComponent* other);

		virtual Collision* checkCollisionCircle(CircleColliderComponent* other) = 0;
		virtual Collision* checkCollisionAABB(AABBColliderComponent* other) = 0;

		bool getIsTrigger() { return m_isTrigger; }
		void setIsTrigger(bool value) { m_isTrigger = value; }

		ColliderType getColliderType() { return m_colliderType; }
		void setColliderType(ColliderType value) { m_colliderType = value; }

		void setIsDebug(bool value) { m_isDebug = value; }
		bool getIsDebug() { return m_isDebug; }

		unsigned int getColor() { return m_color; }

		RigidBodyComponent * getRigidBody() { return m_rigidBody; }

		void onCollision(Collision* collision) override;

		void update(double deltaTime) override;

	private:
		ColliderType m_colliderType;
		bool m_isTrigger;
		bool m_isDebug;
		unsigned int m_color = 0x00FF00FF;
		RigidBodyComponent* m_rigidBody;
	};

	struct Collision
	{
	public:
		ColliderComponent* collider;
		GameMath::Vector3 normal;
		float penetrationDistance;
		GameMath::Vector3 contactPoint;

		
	};
	
}

