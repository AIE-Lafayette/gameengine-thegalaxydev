#include "Shader.h"
#include "glad/glad.h"
#include <iostream>

GameGraphics::Shader::Shader(const char* vertexPath, const char* fragPath)
{
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_fragBufferID);
	glGenVertexArrays(1, &m_vertexArrayID);

	FILE* vertexShaderFile;
	fopen_s(&vertexShaderFile, vertexPath, "rb");

	if (!vertexShaderFile)
	{
		std::cout << "Failed to open vertex shader file." << std::endl;
		return;
	}

	fseek(vertexShaderFile, 0, SEEK_END);
	unsigned int vertexShaderSize = ftell(vertexShaderFile);
	rewind(vertexShaderFile);

	char* vertexShader = new char[vertexShaderSize + 1];

	vertexShader[vertexShaderSize] = '\0';

	fread_s(vertexShader, sizeof(char) * vertexShaderSize + 1, 1, vertexShaderSize, vertexShaderFile);

	fclose(vertexShaderFile);

	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);

	int vertexShaderSuccess;
	char vertexShaderInfoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexShaderSuccess);

	if (!vertexShaderSuccess)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, vertexShaderInfoLog);
		std::cout << "Failed to compile vertex shader." << std::endl;
		std::cout << vertexShaderInfoLog << std::endl;

		delete[] vertexShaderInfoLog;

		return;
	}

	FILE* fragShaderFile;
	fopen_s(&fragShaderFile, fragPath, "rb");

	if (!fragShaderFile)
	{
		std::cout << "Failed to open fragment shader file." << std::endl;
		return;
	}

	fseek(fragShaderFile, 0, SEEK_END);
	unsigned int fragShaderSize = ftell(fragShaderFile);
	rewind(fragShaderFile);

	char* fragShader = new char[fragShaderSize + 1];

	fragShader[fragShaderSize] = '\0';

	fread_s(fragShader, sizeof(char) * fragShaderSize + 1, 1, fragShaderSize, fragShaderFile);

	fclose(fragShaderFile);

	unsigned int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragShaderID, 1, &fragShader, NULL);

	glCompileShader(fragShaderID);

	int fragShaderSuccess;
	char fragShaderInfoLog[512];
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &fragShaderSuccess);

	if (!fragShaderSuccess)
	{
		glGetShaderInfoLog(fragShaderID, 512, NULL, fragShaderInfoLog);
		std::cout << "Failed to compile fragment shader." << std::endl;
		std::cout << fragShaderInfoLog << std::endl;

		delete[] fragShaderInfoLog;

		return;
	}

	m_shaderProgram = glCreateProgram();

	glAttachShader(m_shaderProgram, vertexShaderID);
	glAttachShader(m_shaderProgram, fragShaderID);

	glLinkProgram(m_shaderProgram);

	int linkSuccess;
	char linkInfoLog[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linkSuccess);

	if (!linkSuccess)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, linkInfoLog);
		std::cout << "Failed to link shader program." << std::endl;
		std::cout << linkInfoLog << std::endl;

		delete[] linkInfoLog;

		return;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);
}

void GameGraphics::Shader::use()
{
	glUseProgram(m_shaderProgram);

	glUniform1i(glGetUniformLocation(m_shaderProgram, m_boolData.name), m_boolData.data[0]);
	glUniform1i(glGetUniformLocation(m_shaderProgram, m_intData.name), m_intData.data[0]);
	glUniform1f(glGetUniformLocation(m_shaderProgram, m_floatData.name), m_floatData.data[0]);
	glUniform2f(glGetUniformLocation(m_shaderProgram, m_vec2Data.name), m_vec2Data.data[0], m_vec2Data.data[1]);
	glUniform4f(glGetUniformLocation(m_shaderProgram, m_colorData.name), m_colorData.data[0], m_colorData.data[1], m_colorData.data[2], m_colorData.data[3]);
}

void GameGraphics::Shader::setBool(const char* name, bool value)
{
	//glUniform1i(glGetUniformLocation(m_shaderProgram, name), value);

	m_boolData.name = name;
	m_boolData.data[0] = value;
}

void GameGraphics::Shader::setInt(const char* name, int value)
{
	//glUniform1i(glGetUniformLocation(m_shaderProgram, name), value);

	m_intData.name = name;
	m_intData.data[0] = value;
}

void GameGraphics::Shader::setFloat(const char* name, float value)
{
	//glUniform1f(glGetUniformLocation(m_shaderProgram, name), value);

	m_floatData.name = name;
	m_floatData.data[0] = value;
}

void GameGraphics::Shader::setVec2(const char* name, GameMath::Vector2 value)
{
	//glUniform2f(glGetUniformLocation(m_shaderProgram, name), value.x, value.y);

	m_vec2Data.name = name;
	m_vec2Data.data[0] = value.x;
	m_vec2Data.data[1] = value.y;
}

void GameGraphics::Shader::setVec2(const char* name, float x, float y)
{
	//glUniform2f(glGetUniformLocation(m_shaderProgram, name), x, y);

	m_vec2Data.name = name;
	m_vec2Data.data[0] = x;
	m_vec2Data.data[1] = y;
}

void GameGraphics::Shader::setColor(const char* name, float x, float y, float z, float w)
{
	//glUniform4f(glGetUniformLocation(m_shaderProgram, name), x, y, z, w);

	m_colorData.name = name;
	m_colorData.data[0] = x;
	m_colorData.data[1] = y;
	m_colorData.data[2] = z;
	m_colorData.data[3] = w;
}

void GameGraphics::Shader::setColor(const char* name, GameGraphics::Color4 color)
{
	//glUniform4f(glGetUniformLocation(m_shaderProgram, name), color.getR(), color.getG(), color.getB(), color.getA());

	m_colorData.name = name;
	m_colorData.data[0] = color.getR();
	m_colorData.data[1] = color.getG();
	m_colorData.data[2] = color.getB();
	m_colorData.data[3] = color.getA();
}