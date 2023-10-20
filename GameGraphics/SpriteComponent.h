#pragma once
#include "GameEngine/Component.h"
#include "Shader.h"
#include "GameGraphics/Color4.h"

namespace GameGraphics
{
	enum ScaleType
	{
		STRETCH,
		TILE,
		FIT,
		CROP,
		REPEAT
	};


	class SpriteComponent
		: public GameEngine::Component
	{
	public:
		SpriteComponent();
		SpriteComponent(ScaleType scaleType);
		SpriteComponent(const char* texturePath);
		SpriteComponent(const char* texturePath, ScaleType scaleType);
		SpriteComponent(const char* texturePath, const char* vertexShader, const char* fragShader);
		SpriteComponent(const char* texturePath, const char* vertexShader, const char* fragShader, ScaleType scaleType);

		GameGraphics::Color4 getColor() const { return m_color; }
		void setColor(GameGraphics::Color4 color) { m_color = color; }

		void setTexture(const char* texturePath);

		void draw() override;
		void update(double deltaTime) override {}

		GameGraphics::Shader* getShader() const { return m_spriteShader; }

		ScaleType getScaleType() const { return m_scaleType; }

		void setTileSize(GameMath::Vector2 tileSize) { m_tileSize = tileSize; }
		GameMath::Vector2 getTileSize() { return m_tileSize; }


	private:
		const char* m_texturePath;
		GameGraphics::Shader* m_spriteShader;
		unsigned int m_textureID;
		GameGraphics::Color4 m_color;
		ScaleType m_scaleType = STRETCH;
		GameMath::Vector2 m_tileSize;
	};

}
