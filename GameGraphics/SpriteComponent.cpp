#include "SpriteComponent.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Include/stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include <GameMath/Vector2.h>
#include "Window.h"
#include "GameEngine/TransformComponent.h"

GameGraphics::SpriteComponent::SpriteComponent()
{
	m_spriteShader = new Shader("SpriteShader.vert", "SpriteShader.frag");
}

GameGraphics::SpriteComponent::SpriteComponent(ScaleType scaleType)
{
	m_scaleType = scaleType;
	m_spriteShader = new Shader("SpriteShader.vert", "SpriteShader.frag");
}

GameGraphics::SpriteComponent::SpriteComponent(const char* texturePath)
{
	m_spriteShader = new Shader("SpriteShader.vert", "SpriteShader.frag");
	setTexture(m_texturePath);
}

GameGraphics::SpriteComponent::SpriteComponent(const char* texturePath, ScaleType scaleType)
{
	m_scaleType = scaleType;
	m_spriteShader = new Shader("SpriteShader.vert", "SpriteShader.frag");
	setTexture(texturePath);
}

GameGraphics::SpriteComponent::SpriteComponent(const char* texturePath, const char* vertexShader, const char* fragShader)
{
	m_spriteShader = new Shader(vertexShader, fragShader);
	setTexture(texturePath);
}

GameGraphics::SpriteComponent::SpriteComponent(const char* texturePath, const char* vertexShader, const char* fragShader, ScaleType scaleType)
{
	m_scaleType = scaleType;
	m_spriteShader = new Shader(vertexShader, fragShader);
	setTexture(texturePath);
}

void GameGraphics::SpriteComponent::setTexture(const char* texturePath)
{
	int width;
	int height;
	int nrChannels;

	//Generate a texture buffer and store its ID for future reference.
	glGenTextures(1, &m_textureID);
	//Bind the texture so that all of the calls below apply to it.
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	m_texturePath = texturePath;

	if (m_scaleType == STRETCH)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else if (m_scaleType == TILE)
	{ 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (m_scaleType == FIT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}
	else if (m_scaleType == CROP)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}
	else if (m_scaleType == REPEAT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	//Set the quality settings for resizing the image.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	//Use the library to load the image data.
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 4);

	//If it loaded correctly...
	if (data)
	{
		//...create an image of the appropriate format (jpg = GL_RGB, png = GL_RGBA)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture at " << texturePath << std::endl;
	}
}

void GameGraphics::SpriteComponent::draw()
{
	GameMath::Vector2 scale = getOwner()->getTransform()->getGlobalScale2D();

	float textureScaleX = 1;
	float textureScaleY = 1;

	if (m_scaleType == TILE)
	{
		textureScaleX = scale.x / m_tileSize.x;
		textureScaleY = scale.y / m_tileSize.y;
	}

	GameMath::Vector2 dimensions = GameGraphics::Window::convertToScreenPosition(scale);
	GameMath::Vector2 position = GameGraphics::Window::convertToScreenPosition(getOwner()->getTransform()->getGlobalPosition2D());

	GameMath::Vector2 topRight = { position.x + dimensions.x / 2, position.y + dimensions.y / 2 };
	GameMath::Vector2 topLeft = { position.x - dimensions.x / 2, position.y + dimensions.y / 2 };
	GameMath::Vector2 bottomRight = { position.x + dimensions.x / 2, position.y - dimensions.y / 2 };
	GameMath::Vector2 bottomLeft = { position.x - dimensions.x / 2, position.y - dimensions.y / 2 };

	float vertices[] = {
		topRight.x, topRight.y, 0.0f, textureScaleX,textureScaleY,
		topLeft.x, topLeft.y, 0.0f, 0 , textureScaleY,
		bottomRight.x, bottomRight.y, 0.0f, textureScaleX, 0,
		bottomLeft.x, bottomLeft.y, 0.0f, 0, 0
	};

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	m_spriteShader->use();

	glBindVertexArray(m_spriteShader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_spriteShader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	GameMath::Matrix4 transform = getOwner()->getTransform()->getGlobalMatrix();
	GameMath::Vector2 normalX = GameMath::Vector2(transform.m00, transform.m10).getNormalized();
	GameMath::Vector2 normalY = GameMath::Vector2(transform.m01, transform.m11).getNormalized();

	float transformData[] =
	{
		normalX.x, normalY.x, 0,
		normalX.y, normalY.y, 0,
		transform.m30, transform.m31, transform.m33
	};

	unsigned int transformLocation = glGetUniformLocation(m_spriteShader->getShaderProgram(), "transform");
	glUniformMatrix3fv(transformLocation, 1, GL_FALSE, transformData);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}