#pragma once


namespace GameGraphics
{
	class Gizmos
	{
	public:
		static void init();

	private:
		static unsigned int m_vertexBufferID; 
		static unsigned int m_fragBufferID;
		
		static char* m_vertexShader;
		static char* m_fragShader;
	};
}
