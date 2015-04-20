#pragma once
#include "Material.h"
#include "logger.h"

class TextureQuad
{
public:
	TextureQuad(void);
	TextureQuad(float h, float w, Material* mat);
	~TextureQuad(void);

	
	void SetMatrix(glm::mat4 mvp);
	void SetTexture(GLuint texture);
	
	void Draw();
	void Draw_f(float x, float y);
	void Draw(float x, float y);

	void SetMaterial(Material* newMaterial);

	void SetOrigin(float x, float y);
	void SetOrigin_f(float x, float y);

private:
	float width, height, originX, originY;

	GLuint m_vao, m_vbo, m_bump, m_texture;

	glm::mat4 matrix;

	Material* mat;

	bool Init();

	void LoadTexture(const char* fn, bool repeat);
	void LoadBump(const char* fn, bool repeat);
};

