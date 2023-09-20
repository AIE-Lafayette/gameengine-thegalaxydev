#pragma once
#include "GameEngine\Component.h"
#include <GameMath\Vector3.h>

class InputComponent2D :
    public GameEngine::Component
{

public:

    /// <summary>
    /// Returns a direct ion based on WASD input.
    /// </summary>
    GameMath::Vector3 getMoveDirection();
};

