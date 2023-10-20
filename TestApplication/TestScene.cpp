#include "TestScene.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderComponent.h"
#include "GamePhysics/AABBColliderComponent.h"
#include "InputComponent2D.h"
#include "GameEngine/Engine.h"
#include <iostream>
#include <random>
#include "GameGraphics/SpriteComponent.h"
#include "GameGraphics/Gizmos.h"
#include "WaterSpriteComponent.h"

#include "GameEngine/Input.h"

bool enablePhysics = false;

GameEngine::GameObject* boat;
GameEngine::GameObject* player;
GameEngine::GameObject* fish;

bool isCasted = false;
GameMath::Vector2 castPosition;
float elapsed = 0;
bool mousePressed = false;
bool prevFrameMouseState = false;

void TestScene::onStart()
{
	GameEngine::GameObject* clouds = new GameEngine::GameObject();
	WaterSpriteComponent* cloudSprite = new WaterSpriteComponent("clouds.png", GameGraphics::REPEAT);
	cloudSprite->setOffsetVector({ -0.05f, 0 });
	clouds->addComponent(cloudSprite);
	clouds->getTransform()->setLocalScale({ 800.0f, 800.0f });
	clouds->getTransform()->setLocalPosition({ 0, 0 });

	boat = new GameEngine::GameObject();
	GameGraphics::SpriteComponent* boatSprite = new GameGraphics::SpriteComponent("boat.png", GameGraphics::FIT);
	boat->addComponent(boatSprite);
	boat->getTransform()->setLocalScale({ 300.0f, 300.0f });
	boat->getTransform()->setLocalPosition({ 0, 0 });

	GameEngine::GameObject* boatShadow = new GameEngine::GameObject();
	GameGraphics::SpriteComponent* boatShadowSprite = new GameGraphics::SpriteComponent("boatshadow.png", GameGraphics::FIT);
	boatShadow->addComponent(boatShadowSprite);
	boatShadow->getTransform()->setParent(boat->getTransform());
	boatShadow->getTransform()->setLocalScale(1,1);
	boatShadow->getTransform()->setLocalPosition({ 0, 0 });

	GameEngine::GameObject* water = new GameEngine::GameObject();
	WaterSpriteComponent* waterSprite = new WaterSpriteComponent("tile_water.png", GameGraphics::TILE);
	waterSprite->setTileSize({ 200, 200 });
	waterSprite->setOffsetVector({ -0.5f, 0.0f });
	water->addComponent(waterSprite);
	water->getTransform()->setLocalScale({ 800.0f, 600.0f });
	water->getTransform()->setLocalPosition({0, -300});

	player = new GameEngine::GameObject();
	GameGraphics::SpriteComponent* playerSprite = new GameGraphics::SpriteComponent("fisherman.png", GameGraphics::FIT);
	player->addComponent(playerSprite);
	player->getTransform()->setParent(boat->getTransform());
	player->getTransform()->setLocalScale(0.5, 0.5);
	player->getTransform()->setLocalPosition({ 0.05, 0.1 });

	fish = new GameEngine::GameObject();
	GameGraphics::SpriteComponent* fishSprite = new GameGraphics::SpriteComponent("fish.png", GameGraphics::FIT);
	fish->addComponent(fishSprite);
	fish->getTransform()->setLocalScale({ 500.0f, 500.0f });
	fish->getTransform()->setLocalPosition({ 0, 150 });
	fish->setEnabled(false);


	addGameObject(fish);
	addGameObject(player);
	addGameObject(boat);
	addGameObject(boatShadow);
	addGameObject(water);
	addGameObject(clouds);




	
}


void TestScene::onUpdate(double deltaTime)
{
	// this is really dumb but I don't want to fix it right now
	bool currentFrameMouseState = GameEngine::Input::isMouseButtonDown(0);

	if (currentFrameMouseState && !prevFrameMouseState)
	{
		mousePressed = true;
	}
	else
	{
		mousePressed = false;
	}

	prevFrameMouseState = currentFrameMouseState;

	

	if (mousePressed)
	{
		std::cout << "Mouse pressed: " << mousePressed << std::endl;
		if (!isCasted)
		{
			GameMath::Vector2 mousePos = GameEngine::Input::getMousePosition();

			std::cout << mousePos.x << ", " << mousePos.y << std::endl;

			// mouse gotta be in da wata
			if (mousePos.y > 0 || mousePos.x < -400 || mousePos.x > 400)
				return;

			fish->setEnabled(false);
			isCasted = true;

			castPosition = mousePos;
		}
		else
		{
			// catch a fish maybe i dunno 
			fish->setEnabled(true);
			isCasted = false;
		}

	}
}

void TestScene::onDraw()
{

	GameMath::Vector2 offset = { -40, 65 };
	GameMath::Vector2 startPos = player->getTransform()->getGlobalPosition2D() + offset;

	if (isCasted)
	{
		GameGraphics::Gizmos::drawLine(startPos, castPosition, { 1,1,1,1 });
	}
	

	
}
	
void TestScene::onFixedUpdate()
{

}
