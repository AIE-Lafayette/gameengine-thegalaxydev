#pragma once
#include "GameEngine/GameObject.h"

namespace GameGraphics
{
	class ShapeComponent;
}

namespace GamePhysics
{
	class RigidBodyComponent;
	class AABBColliderComponent;
};

class Bumper :
    public GameEngine::GameObject
{
public:
	Bumper();

	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onFixedUpdate() override;
	void onDraw() override;

	void onCollision(GamePhysics::Collision* other) override;

	GamePhysics::AABBColliderComponent* getCollider() { return m_collider; }
private:
	GameGraphics::ShapeComponent* m_shapeComponent;
	GamePhysics::AABBColliderComponent* m_collider;
};

