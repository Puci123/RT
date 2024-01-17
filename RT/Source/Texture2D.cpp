#include "Texture2D.h"
#include "DebugUtilty.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Stbi/stb_image.h"

Texture2D::Texture2D(uint32_t width, uint32_t height) 
	:m_RenderID(0), m_Width(width), m_Height(height)
{
	m_TextureBuffer = new mu::vec4[m_Height * m_Width];

	for (uint32_t i = 0; i < width * height; i++)
	{
		m_TextureBuffer[i] = mu::vec4(static_cast<float>(mu::randomDouble()), static_cast<float>(mu::randomDouble()), static_cast<float>(mu::randomDouble()), 1.f);
	}

	// Create Image on GPU side
	glGenTextures(1, &m_RenderID);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0]);
	Unbind();

	std::cout << "Created texture with dim: " << m_Width << "x" << m_Height << " (ID " << m_RenderID << ")" << std::endl;

}

Texture2D::Texture2D(const std::string& path)
	:m_Height(0), m_Width(0), m_RenderID(0)
{
	//TO D0: Make it work with float as buffer data type

	stbi_set_flip_vertically_on_load(1);
	stbi_hdr_to_ldr_gamma(2.2f);
	int32_t bits;

	m_TextureBuffer = reinterpret_cast<mu::vec4*>(stbi_loadf(path.c_str(), &m_Width, &m_Height, &bits, 4));
	
	

	(glGenTextures(1, &m_RenderID));
	(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


	(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_FLOAT, &m_TextureBuffer[0]));
	(glBindTexture(GL_TEXTURE_2D,0));


}

Texture2D::~Texture2D()
{
	std::cout << "Texture destroyed with ID " << m_RenderID << std::endl;
	delete[] m_TextureBuffer;
	glDeleteTextures(1, &m_RenderID);

}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RenderID);

}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);

}


void Texture2D::SetPixel(uint32_t x, uint32_t y, mu::vec3 color)
{
	ASSERT_L((x < m_Width && y < m_Height), " index of out texture bounds");
	m_TextureBuffer[y * m_Width + x] = mu::vec4(static_cast<float>(color.x), static_cast<float>(color.y), static_cast<float>(color.z), 1.f);

}

void Texture2D::Update()
{
	Bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0].x);
	Unbind();
}
