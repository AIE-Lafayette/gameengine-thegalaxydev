#pragma once
#include "GameGraphics/SpriteComponent.h"
#include "GameMath/Vector2.h"

class WaterSpriteComponent :
    public GameGraphics::SpriteComponent
{
public:
    WaterSpriteComponent(const char* texturePath) : GameGraphics::SpriteComponent(texturePath, "WaterShader.vert", "WaterShader.frag") {}
    WaterSpriteComponent(const char* texturePath, GameGraphics::ScaleType scaleType) : GameGraphics::SpriteComponent(texturePath, "WaterShader.vert", "WaterShader.frag", scaleType) {}


    /// <summary>
    ///moves the texture in the direction of the offset (m_offset)
    /// </summary>
    /// <param name="deltaTime">The amount of time that has passed between frames.</param>
    void update(double deltaTime) override;

    void setOffsetVector(GameMath::Vector2 offsetVector) { m_OffsetVector = offsetVector; }

private:
    GameMath::Vector2 m_offset; 
    GameMath::Vector2 m_OffsetVector = { 0.0f, 0.0f };
};

