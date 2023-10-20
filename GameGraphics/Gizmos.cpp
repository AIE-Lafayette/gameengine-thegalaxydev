#include "Gizmos.h"
#include <glad/glad.h>
#include <iostream>
#include "GameGraphics/Window.h"

#include <vector>;

GameGraphics::Shader* GameGraphics::Gizmos::m_shader = nullptr;

inline GameMath::Vector4 UIntToV4(unsigned int value)
{
	GameMath::Vector4 output;

	output.x = ((value & 0xFF000000) >> 24) / 255.0f;
	output.y = ((value & 0x00FF0000) >> 16) / 255.0f;
	output.z = ((value & 0x0000FF00) >> 8) / 255.0f;
	output.w = ((value & 0x000000FF)) / 255.0f;

	return output;
}

float toRadians(float degrees)
{
	return degrees * (3.14159265358979323846f / 180.0f);
}

void GameGraphics::Gizmos::init()
{
	m_shader = new Shader("GizmoShader.vert", "GizmoShader.frag");
}

void GameGraphics::Gizmos::drawTriangle(GameMath::Vector2 p1, GameMath::Vector2 p2, GameMath::Vector2 p3, GameGraphics::Color4 color)
{
	p1 = GameGraphics::Window::convertToScreenPosition(p1);
	p2 = GameGraphics::Window::convertToScreenPosition(p2);
	p3 = GameGraphics::Window::convertToScreenPosition(p3);

	float vertices[] = {
		p1.x, p1.y, 0.0f,
		p2.x, p2.y, 0.0f,
		p3.x, p3.y, 0.0f
	};

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shader->getFragBufferID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());

	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void GameGraphics::Gizmos::drawTriangleLines(GameMath::Vector2 p1, GameMath::Vector2 p2, GameMath::Vector2 p3, GameGraphics::Color4 color)
{
	p1 = GameGraphics::Window::convertToScreenPosition(p1);
	p2 = GameGraphics::Window::convertToScreenPosition(p2);
	p3 = GameGraphics::Window::convertToScreenPosition(p3);

	float vertices[] = {
		p1.x, p1.y, 0.0f,
		p2.x, p2.y, 0.0f,
		p3.x, p3.y, 0.0f
	};

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shader->getFragBufferID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());

	glDrawArrays(GL_LINE_LOOP, 0, 3);
}

void GameGraphics::Gizmos::drawRectangle(GameMath::Vector2 position, float width, float height, float rotation, GameGraphics::Color4 color)
{
	GameMath::Vector2 size = GameMath::Vector2(width, height);

	GameMath::Vector2 p1 = Window::convertToScreenPosition(position + GameMath::Vector2(-size.x / 2.0f, -size.y / 2.0f)); 
	GameMath::Vector2 p2 = Window::convertToScreenPosition(position + GameMath::Vector2(size.x / 2.0f, -size.y / 2.0f)); 
	GameMath::Vector2 p3 = Window::convertToScreenPosition(position + GameMath::Vector2(size.x / 2.0f, size.y / 2.0f)); 
	GameMath::Vector2 p4 = Window::convertToScreenPosition(position + GameMath::Vector2(-size.x / 2.0f, size.y / 2.0f));

	p1.x = p1.x * cos(rotation) - p1.y * sin(rotation);
	p1.y = p1.x * sin(rotation) + p1.y * cos(rotation);

	p2.x = p2.x * cos(rotation) - p2.y * sin(rotation);
	p2.y = p2.x * sin(rotation) + p2.y * cos(rotation);

	p3.x = p3.x * cos(rotation) - p3.y * sin(rotation);
	p3.y = p3.x * sin(rotation) + p3.y * cos(rotation);

	p4.x = p4.x * cos(rotation) - p4.y * sin(rotation);
	p4.y = p4.x * sin(rotation) + p4.y * cos(rotation);


	float vertices[] = {
		p1.x, p1.y, 0.0f,
		p2.x, p2.y, 0.0f,
		p3.x, p3.y, 0.0f,
		p4.x, p4.y, 0.0f
	};

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shader->getFragBufferID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GameGraphics::Gizmos::drawLine(GameMath::Vector2 start, GameMath::Vector2 end, GameGraphics::Color4 color)
{
	GameMath::Vector2 p1 = Window::convertToScreenPosition(start);
	GameMath::Vector2 p2 = Window::convertToScreenPosition(end);

	float vertices[] = {
		p1.x, p1.y, 0.0f,
		p2.x, p2.y, 0.0f
	};

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shader->getFragBufferID());

	glVertexAttribPointer(0, 3	, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());

	glDrawArrays(GL_LINES, 0, 2);
}

void GameGraphics::Gizmos::drawRectangle(GameMath::Vector2 position, float width, float height, GameGraphics::Color4 color)
{
	drawRectangle(position, width, height, 0.0f, color);
}

void GameGraphics::Gizmos::drawRectangleLines(GameMath::Vector2 position, float width, float height, float rotation, GameGraphics::Color4 color)
{
	GameMath::Vector2 size = GameMath::Vector2(width, height);

	GameMath::Vector2 p1 = Window::convertToScreenPosition(position + GameMath::Vector2(-size.x / 2.0f, -size.y / 2.0f));
	GameMath::Vector2 p2 = Window::convertToScreenPosition(position + GameMath::Vector2(size.x / 2.0f, -size.y / 2.0f));
	GameMath::Vector2 p3 = Window::convertToScreenPosition(position + GameMath::Vector2(size.x / 2.0f, size.y / 2.0f));
	GameMath::Vector2 p4 = Window::convertToScreenPosition(position + GameMath::Vector2(-size.x / 2.0f, size.y / 2.0f));

	rotation = toRadians(rotation);

	p1.x = p1.x * cos(rotation) - p1.y * sin(rotation);
	p1.y = p1.x * sin(rotation) + p1.y * cos(rotation);

	p2.x = p2.x * cos(rotation) - p2.y * sin(rotation);
	p2.y = p2.x * sin(rotation) + p2.y * cos(rotation);

	p3.x = p3.x * cos(rotation) - p3.y * sin(rotation);
	p3.y = p3.x * sin(rotation) + p3.y * cos(rotation);

	p4.x = p4.x * cos(rotation) - p4.y * sin(rotation);
	p4.y = p4.x * sin(rotation) + p4.y * cos(rotation);

	float vertices[] = {
		p1.x, p1.y, 0.0f,
		p2.x, p2.y, 0.0f,
		p3.x, p3.y, 0.0f,
		p4.x, p4.y, 0.0f
	};

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shader->getFragBufferID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());

	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void GameGraphics::Gizmos::drawRectangleLines(GameMath::Vector2 position, float width, float height, GameGraphics::Color4 color)
{
	drawRectangleLines(position, width, height, 0.0f, color);
}


void GameGraphics::Gizmos::drawCircle(GameMath::Vector2 position, float radius, int slices, GameGraphics::Color4 color)
{	
	float angle = 360.0f / slices;

	int triangleCount = slices - 2;

	std::vector<GameMath::Vector2> vertices;

	std::vector<GameMath::Vector2> temp;

	for (int i = 0; i < slices; i++)
	{
		float x = position.x + (radius * cos(toRadians(angle * i)));
		float y = position.y + (radius * sin(toRadians(angle * i)));

		temp.push_back(Window::convertToScreenPosition(GameMath::Vector2(x, y)));
	}

	for (int i = 0; i < triangleCount; i++)
	{
		vertices.push_back(temp[0]);
		vertices.push_back(temp[i + 1]);
		vertices.push_back(temp[i + 2]);
	}

	float* vertexArray = new float[vertices.size() * 3];
	
	for (int i = 0; i < vertices.size(); i++)
	{
		vertexArray[i * 3] = vertices[i].x;
		vertexArray[i * 3 + 1] = vertices[i].y;
		vertexArray[i * 3 + 2] = 0.0f;
	}

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size() * 3, vertexArray, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shader->getFragBufferID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());

	
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	delete[] vertexArray;
}

void GameGraphics::Gizmos::drawCircleLines(GameMath::Vector2 position, float radius, int slices, GameGraphics::Color4 color)
{
	float angle = 360.0f / slices;

	std::vector<GameMath::Vector2> vertices;

	for (int i = 0; i < slices; i++)
	{
		float x = position.x + (radius * cos(toRadians(angle * i)));
		float y = position.y + (radius * sin(toRadians(angle * i)));

		vertices.push_back(Window::convertToScreenPosition(GameMath::Vector2(x, y)));
	}

	float* vertexArray = new float[vertices.size() * 3];

	for (int i = 0; i < vertices.size(); i++)
	{
		vertexArray[i * 3] = vertices[i].x;
		vertexArray[i * 3 + 1] = vertices[i].y;
		vertexArray[i * 3 + 2] = 0.0f;
	}

	glBindVertexArray(m_shader->getVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, m_shader->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size() * 3, vertexArray, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	m_shader->use();

	int colorLocation = glGetUniformLocation(m_shader->getShaderProgram(), "color");
	glUniform4f(colorLocation, color.getR(), color.getG(), color.getB(), color.getA());
	
	glDrawArrays(GL_LINE_LOOP, 0, vertices.size());

	delete[] vertexArray;
}

