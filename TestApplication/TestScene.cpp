#include "TestScene.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderComponent.h"
#include "GamePhysics/AABBColliderComponent.h"
#include "InputComponent2D.h"
#include "GameEngine/Engine.h"
#include "Raylib/raylib.h"

#include <iostream>
#include <random>


bool enablePhysics = false;

GameEngine::GameObject* immovableObject;

void centerOnScreen(GameEngine::TransformComponent* transform, GameMath::Vector3 offset)
{
	// set position based on scale
	GameMath::Vector3 position = transform->getLocalPosition();
	GameMath::Vector3 scale = transform->getLocalScale();

	position.x = (400) - (scale.x / 2);
	position.y = (400) - (scale.y / 2);

	transform->setLocalPosition(position + offset);
}
GameEngine::GameObject* makePlatform(GameMath::Vector3 position, GameMath::Vector3 size)
{
	GameEngine::GameObject* platform = new GameEngine::GameObject();

	platform->getTransform()->setLocalScale(size);
	platform->getTransform()->setLocalPosition(position);
	GamePhysics::RigidBodyComponent* rigidBody2 = platform->addComponent<GamePhysics::RigidBodyComponent>();
	rigidBody2->setIsKinematic(true);
	GamePhysics::AABBColliderComponent* collider = platform->addComponent<GamePhysics::AABBColliderComponent>();
	collider->setSize(platform->getTransform()->getLocalScale());
	collider->setIsDebug(true);
	GameGraphics::ShapeComponent* shape = platform->addComponent<GameGraphics::ShapeComponent>();
	shape->setShapeType(GameGraphics::CUBE);
	shape->setColor(0x000000FF);

	rigidBody2->setStaticFrictionCoefficient(60);
	rigidBody2->setDynamicFrictionCoefficient(100);

	return platform;
}

void TestScene::onStart()
{
	//platform under player

	//floor
	addGameObject(makePlatform({400,790, 0 }, { 800, 20, 0 }));
	addGameObject(makePlatform({ 400,10, 0 }, { 800, 20, 0 }));
	addGameObject(makePlatform({ 10,400, 0 }, { 20, 800, 0 }));
	addGameObject(makePlatform({ 790,400, 0 }, { 20, 800, 0 }));

	immovableObject = new GameEngine::GameObject();
	immovableObject->getTransform()->setLocalScale({ 50.0f, 50.0f, 0.0f });
	immovableObject->getTransform()->setLocalPosition({ 380, 300, 0 });
	immovableObject->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CUBE);
	immovableObject->addComponent<GamePhysics::AABBColliderComponent>()->setSize(immovableObject->getTransform()->getLocalScale());

	GamePhysics::RigidBodyComponent* rigidBody = immovableObject->addComponent<GamePhysics::RigidBodyComponent>();
	rigidBody->setStaticFrictionCoefficient(40.0f);
	rigidBody->setDynamicFrictionCoefficient(100.0f);

	addGameObject(immovableObject);

}

double elapsed = 0;
void TestScene::onUpdate(double deltaTime)
{
	if (IsKeyPressed(KEY_E))
	{
		GameEngine::GameObject* ball = new GameEngine::GameObject();

		GameMath::Vector3 mousePosition = { (float)GetMouseX(), (float)GetMouseY(), 0 };

		ball->getTransform()->setLocalScale({ 20.0f, 20.0f, 0.0f });
		ball->getTransform()->setLocalPosition(mousePosition);
		GameGraphics::ShapeComponent* shape = ball->addComponent<GameGraphics::ShapeComponent>();
		shape->setShapeType(GameGraphics::CUBE);
		ball->addComponent<GamePhysics::AABBColliderComponent>()->setSize(ball->getTransform()->getLocalScale());
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<uint32_t> dis(0, UINT32_MAX);
		shape->setColor(dis(gen));

		GamePhysics::RigidBodyComponent* rigidBody = ball->addComponent<GamePhysics::RigidBodyComponent>();
		rigidBody->setStaticFrictionCoefficient(0.3f);
		rigidBody->setDynamicFrictionCoefficient(0.15f);

		rigidBody->setElasticity(0.0f);
		rigidBody->setMass(1.0f);
		GameMath::Vector3 direction = (immovableObject->getTransform()->getGlobalPosition() - mousePosition).getNormalized();
		rigidBody->applyForce(direction * 200);

		

		addGameObject(ball);
	}
}
	
void TestScene::onFixedUpdate()
{
}
