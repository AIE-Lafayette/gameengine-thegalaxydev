#include "Gizmos.h"
#include <glad/glad.h>
#include <iostream>

unsigned int GameGraphics::Gizmos::m_vertexBufferID = 0;
char* GameGraphics::Gizmos::m_vertexShader = nullptr;
unsigned int GameGraphics::Gizmos::m_fragBufferID = 0;
char* GameGraphics::Gizmos::m_fragShader = nullptr;

void GameGraphics::Gizmos::init()
{
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_fragBufferID);

	FILE* vertexShaderFile;
	fopen_s(&vertexShaderFile, "Shaders/GizmoShader.vert", "rb");

	if (!vertexShaderFile)
	{
		std::cout << "Failed to open vertex shader file." << std::endl;
		return;
	}

	fseek(vertexShaderFile, 0, SEEK_END);
	unsigned int vertexShaderSize = ftell(vertexShaderFile);
	rewind(vertexShaderFile);

	m_vertexShader = new char[vertexShaderSize + 1];

	m_vertexShader[vertexShaderSize] = '\0';

	fread_s(m_vertexShader, sizeof(char) * vertexShaderSize + 1, 1, vertexShaderSize, vertexShaderFile);
}