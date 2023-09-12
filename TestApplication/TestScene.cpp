#include "TestScene.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderComponent.h"
#include "GamePhysics/AABBColliderComponent.h"

#include <iostream>

GameEngine::GameObject* circle;
GameEngine::GameObject* box;

void TestScene::onStart()
{
	circle = new GameEngine::GameObject();

	GameGraphics::ShapeComponent* shapeComponent = circle->addComponent<GameGraphics::ShapeComponent>();
	shapeComponent->setShapeType(GameGraphics::CUBE);

	GamePhysics::RigidBodyComponent* rigidBody = circle->addComponent<GamePhysics::RigidBodyComponent>();
	circle->addComponent<GamePhysics::AABBColliderComponent>()->setSize({ 50, 50, 0 });
	rigidBody->setElasticity(0);

	box = new GameEngine::GameObject();
	box->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CUBE);

	GamePhysics::RigidBodyComponent* rigidBody2 = box->addComponent<GamePhysics::RigidBodyComponent>();
	box->addComponent<GamePhysics::AABBColliderComponent>()->setSize({ 50, 50, 0 });
	rigidBody2->setGravity(0);
	rigidBody2->setIsKinematic(true);

	circle->getTransform()->setLocalPosition({ 100.0f, 100.0f });
	circle->getTransform()->setLocalScale({ 20.0f, 20.0f, 0.0f });

	box->getTransform()->setLocalPosition({ 100.0f, 400.0f });
	box->getTransform()->setLocalScale({ 20.0f, 20.0f, 0.0f });

	addGameObject(circle);
	addGameObject(box);
}

double elapsed = 0;
void TestScene::onUpdate(double deltaTime)
{
}