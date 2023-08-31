#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
    class AABBColliderComponent :
        public ColliderComponent
    {
        public:
		AABBColliderComponent() {}

		Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		Collision* checkCollisionCircle(AABBColliderComponent* other) override;

		Collision* checkCollisionAABB(AABBColliderComponent* other) override;
		Collision* checkCollisionAABB(CircleColliderComponent* other) override;

		GameMath::Vector3 getHalfSize() { return m_halfSize; }
		void setHalfSize(GameMath::Vector3 value) { m_halfSize = value; }

	private:
		GameMath::Vector3 m_halfSize;
    };
}


