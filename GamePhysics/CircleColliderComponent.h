#pragma once
#include "ColliderComponent.h"

namespace GamePhysics {
	class CircleColliderComponent :
		public ColliderComponent
	{
	public:
		CircleColliderComponent(float radius) { m_radius = radius; }
		CircleColliderComponent() {}

		Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		Collision* checkCollisionCircle(AABBColliderComponent* other) override;

		Collision* checkCollisionAABB(AABBColliderComponent* other) override;
		Collision* checkCollisionAABB(CircleColliderComponent* other) override;

		float getRadius() { return m_radius; }
		void setRadius(float value) { m_radius = value; }

		void draw() override;

	private:
		float m_radius;
	};
}


