#pragma once
#include <GL/glew.h>
#include<vector>

#include "MathUtility.h"

class Texture2D
{
	public:
		Texture2D(uint32_t width, uint32_t height);
		~Texture2D();


		void Bind();
		void Unbind();

		void SetPixel(uint32_t x, uint32_t y, mu::vec3 color);
		void Update();
		
		inline uint32_t GetWidth()	const  { return m_Width; }
		inline uint32_t GetHeight() const  { return m_Height; }
		inline uint32_t GetID()     const { return m_RenderID; }
		inline mu::vec4 GetPixel(int32_t x, int32_t y) const { return m_TextureBuffer[y * m_Width + x]; }


	private:
		uint32_t m_RenderID;
		uint32_t m_Width;
		uint32_t m_Height;

		std::vector<mu::vec4> m_TextureBuffer;

};

