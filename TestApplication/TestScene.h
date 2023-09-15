#pragma once
#include "GameEngine/Scene.h"

class TestScene :
    public GameEngine::Scene
{
    void onStart() override;
    void onUpdate(double deltaTime) override;
    void onFixedUpdate() override;
};

