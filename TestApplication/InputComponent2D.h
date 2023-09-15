#pragma once
#include "GameEngine\Component.h"
#include <GameMath\Vector3.h>

class InputComponent2D :
    public GameEngine::Component
{

public:
    GameMath::Vector3 getMoveDirection();
};

