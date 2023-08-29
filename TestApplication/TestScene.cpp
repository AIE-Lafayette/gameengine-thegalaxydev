#include "TestScene.h"
#include <ShapeComponent.h>
#include <RigidBodyComponent.h>

void TestScene::onStart()
{
	GameEngine::GameObject* circle = new GameEngine::GameObject();
	circle->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	circle->addComponent<GamePhysics::RigidBodyComponent>();

	circle->getTransform()->setLocalPosition({ 100.0f, 100.0f });
	circle->getTransform()->setLocalScale({ 25.0f, 25.0f, 0.0f });

	addGameObject(circle);
}
