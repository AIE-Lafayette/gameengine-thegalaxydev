#include "TestScene.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderComponent.h"
#include "GamePhysics/AABBColliderComponent.h"

GameEngine::GameObject* circle;
GameEngine::GameObject* box;

void TestScene::onStart()
{
	circle = new GameEngine::GameObject();

	GameGraphics::ShapeComponent* shapeComponent = circle->addComponent<GameGraphics::ShapeComponent>();
	shapeComponent->setShapeType(GameGraphics::SPHERE);

	GamePhysics::RigidBodyComponent* rigidBody = circle->addComponent<GamePhysics::RigidBodyComponent>();
	circle->addComponent<GamePhysics::CircleColliderComponent>()->setRadius(30);

	box = new GameEngine::GameObject();
	box->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CUBE);

	GamePhysics::RigidBodyComponent* rigidBody2 = box->addComponent<GamePhysics::RigidBodyComponent>();
	box->addComponent<GamePhysics::AABBColliderComponent>()->setSize({ 30, 30, 0 });
	rigidBody2->setGravity(0);

	circle->getTransform()->setLocalPosition({ 100.0f, 150.0f });
	circle->getTransform()->setLocalScale({ 25.0f, 25.0f, 0.0f });

	box->getTransform()->setLocalPosition({ 100.0f, 200.0f });
	box->getTransform()->setLocalScale({ 25.0f, 25.0f, 0.0f });

	addGameObject(circle);
	addGameObject(box);
}

double elapsed = 0;
void TestScene::onUpdate(double deltaTime)
{
	elapsed += deltaTime;

	if (elapsed > 0.75)
	{
		elapsed = 0;
		GamePhysics::RigidBodyComponent* rigidBody = circle->getComponent<GamePhysics::RigidBodyComponent>();
		rigidBody->setVelocity2D({ 0, 0 });
		rigidBody->setGravity(-rigidBody->getGravity());
	}
}