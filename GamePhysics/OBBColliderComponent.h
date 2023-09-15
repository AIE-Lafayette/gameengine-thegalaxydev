#pragma once
#include "ColliderComponent.h"
namespace GamePhysics
{
	class OBBColliderComponent :
		public GamePhysics::ColliderComponent
	{
	public:
		OBBColliderComponent();
		OBBColliderComponent(GameMath::Vector3 size);
		OBBColliderComponent(GameMath::Vector2 size);

		Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		Collision* checkCollisionAABB(AABBColliderComponent* other) override;
		Collision* checkCollisionOBB(OBBColliderComponent* other) override;

		float* projectOntoAxis(GameMath::Vector3* vertices, GameMath::Vector3 axis);

		void draw() override;

		GameMath::Vector3 getExtents();
		GameMath::Vector3 getCenter();
		GameMath::Vector3 getOrientation();
		GameMath::Vector3* getVertices();

		GameMath::Vector3 getSize() { return m_size; }
		void setSize(GameMath::Vector3 value) { m_size = value; }


	private:
		GameMath::Vector3 m_size;

	};


}
