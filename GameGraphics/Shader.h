#pragma once

#include <GameMath/Vector2.h>;
#include "GameGraphics/Color4.h"

namespace GameGraphics
{
	template<typename T, int size>
	struct UniformData
	{
		const char* name = "";
		T data[size];
	};

	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragPath);

		unsigned int getShaderProgram() const { return m_shaderProgram; }
		unsigned int getVertexArrayID() const { return m_vertexArrayID; }
		unsigned int getVertexBufferID() const { return m_vertexBufferID; }
		unsigned int getFragBufferID() const { return m_fragBufferID; }

		void use();

		void setBool(const char* name, bool value);
		void setInt(const char* name, int value);
		void setFloat(const char* name, float value);
		void setVec2(const char* name, GameMath::Vector2 value);
		void setVec2(const char* name, float x, float y);

		void setColor(const char* name, float x, float y, float z, float w);
		void setColor(const char* name, GameGraphics::Color4 color);
	private:
		unsigned int m_vertexBufferID;	
		unsigned int m_fragBufferID;
		unsigned int m_shaderProgram;
		unsigned int m_vertexArrayID;

		GameGraphics::UniformData<bool, 1> m_boolData;
		GameGraphics::UniformData<int, 1> m_intData;
		GameGraphics::UniformData<float, 1> m_floatData;
		GameGraphics::UniformData<float, 2> m_vec2Data;
		GameGraphics::UniformData<float, 4> m_colorData;

	};
}
