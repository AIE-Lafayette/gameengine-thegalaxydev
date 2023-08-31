#include "TestScene.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderComponent.h"

GameEngine::GameObject* circle;
GameEngine::GameObject* circle2;

void TestScene::onStart()
{
	circle = new GameEngine::GameObject();

	GameGraphics::ShapeComponent* shapeComponent = circle->addComponent<GameGraphics::ShapeComponent>();
	shapeComponent->setShapeType(GameGraphics::CIRCLE);

	GamePhysics::RigidBodyComponent* rigidBody = circle->addComponent<GamePhysics::RigidBodyComponent>();
	circle->addComponent<GamePhysics::CircleColliderComponent>()->setRadius(30);

	circle2 = new GameEngine::GameObject();
	circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);

	GamePhysics::RigidBodyComponent* rigidBody2 = circle2->addComponent<GamePhysics::RigidBodyComponent>();
	circle2->addComponent<GamePhysics::CircleColliderComponent>()->setRadius(30);
	rigidBody2->setGravity(0);

	circle->getTransform()->setLocalPosition({ 100.0f, 100.0f });
	circle->getTransform()->setLocalScale({ 25.0f, 25.0f, 0.0f });

	circle2->getTransform()->setLocalPosition({ 100.0f, 200.0f });
	circle2->getTransform()->setLocalScale({ 25.0f, 25.0f, 0.0f });

	addGameObject(circle);
	addGameObject(circle2);
}

double elapsed = 0;
void TestScene::onUpdate(double deltaTime)
{
	elapsed += deltaTime;

	if (elapsed > 1)
	{
		elapsed = 0;
		GamePhysics::RigidBodyComponent* rigidBody = circle->getComponent<GamePhysics::RigidBodyComponent>();
		rigidBody->setGravity(-rigidBody->getGravity());
	}

}