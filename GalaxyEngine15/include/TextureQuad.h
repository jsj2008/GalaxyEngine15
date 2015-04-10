#pragma once
#include "ShaderPair.h"
#include "Texture.h"

class TextureQuad
{
public:
	TextureQuad();
	TextureQuad(float h, float w);
	TextureQuad(float h, float w, const char* fn, bool resize = false, bool repeat= false);
	~TextureQuad(void);

	void Init();
	void SetMatrix(glm::mat4 mvp);
	void SetTexture(GLuint texture);
	
	void Draw();
	void Draw(float x, float y);
	void DrawBump(float x, float y);

private:
	bool  m_repeat;
	float width, height;

	GLuint m_vao, m_vbo, m_bump, m_texture;

	glm::mat4 matrix;

	ShaderPair* shader;
	tdogl::Texture* textureObject;

	void LoadTexture(const char* fn, bool repeat);
	void LoadBump(const char* fn, bool repeat);
};

