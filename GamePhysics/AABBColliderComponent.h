#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
    class AABBColliderComponent :
        public ColliderComponent
    {
     public:
		AABBColliderComponent();
		AABBColliderComponent(GameMath::Vector3 size);
		AABBColliderComponent(GameMath::Vector2 size);

		Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		GameMath::Vector3 getPenetrationVector(AABBColliderComponent* other);

		void draw() override;

		float getRight();
		float getUp();
		float getFront();
		float getDown();
		float getLeft();
		float getBack();

		GameMath::Vector3 getSize() { return m_size; }
		void setSize(GameMath::Vector3 value) { m_size = value; }


	private:
		GameMath::Vector3 m_size;
    };
}


