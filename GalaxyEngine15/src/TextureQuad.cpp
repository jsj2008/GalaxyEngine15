#include "..\include\TextureQuad.h"


TextureQuad::TextureQuad()
{
	height = 0;
	width = 0;
}

TextureQuad::TextureQuad(float w, float h)
{
	height = h;
	width = w;
}

TextureQuad::TextureQuad(float w, float h, const char* fn, bool resize, bool repeat)
{
	LoadTexture(fn, repeat);

	m_repeat = repeat;

	if(resize)
	{
		height = textureObject->originalHeight();
		width = textureObject->originalWidth();
	}else
	{
		height = h;
		width =	w;
	}

	m_texture = textureObject->object();

}

TextureQuad::~TextureQuad(void)
{
}

void TextureQuad::Init()
{
	// Make shaders
	shader = new ShaderPair();
	shader->Init("quadShader.vert", "quadShader.frag");

	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);

	// bind the VAO
	glBindVertexArray(m_vao);

	// bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	float uvMaxH= 1.0f;
	float uvMaxW= 1.0f;

	if(m_repeat)
	{
		uvMaxH = uvMaxW = /*screenwidth*/800 / textureObject->originalWidth();
	}

	// Set to full screen
	if(height == 0 && width == 0)
	{
		// Quad vertices
		GLfloat qdata[] = {
			 0.0f, 0.0f, 0.0f, 0.0f,   0.0f, // Top left
			 1.0f, 0.0f, 0.0f, uvMaxW, 0.0f, // Top right
			 1.0f, 1.0f, 0.0f, uvMaxW, uvMaxH, // Bottom right
			 0.0f, 1.0f, 0.0f, 0.0f,   uvMaxH  // Bottom left
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(qdata), qdata, GL_STATIC_DRAW);
	}else // probably ortho drawing
	{
		// Quad vertices
		GLfloat qdata[] = {
			0.0f,  0.0f,   0.0f, 0.0f, 0.0f, // Top left
			width, 0.0f,   0.0f, uvMaxW, 0.0f, // Top right
			width, height, 0.0f, uvMaxW, uvMaxH, // Bottom right
			0.0f,  height, 0.0f, 0.0f, uvMaxH  // Bottom left
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(qdata), qdata, GL_STATIC_DRAW);
	}

	// connect the xyz coords
	glEnableVertexAttribArray(shader->GetAttribLocation("vertex"));
	glVertexAttribPointer(shader->GetAttribLocation("vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);

	// connect the uv coords to the tex coords
	glEnableVertexAttribArray(shader->GetAttribLocation("uv"));
	glVertexAttribPointer(shader->GetAttribLocation("uv"), 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	// unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TextureQuad::SetTexture(GLuint texture)
{
	m_texture = texture;
}

void TextureQuad::LoadTexture(const char* fn, bool repeat)
{
	// Load the texture object
	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(fn);
	bmp.flipVertically();

	if(repeat)
		textureObject = new tdogl::Texture(bmp, GL_LINEAR, GL_REPEAT);
	else
		textureObject = new tdogl::Texture(bmp);
}

void TextureQuad::LoadBump(const char* fn, bool repeat)
{
	// Load the texture object
	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(fn);
	bmp.flipVertically();

	if(repeat)
		textureObject = new tdogl::Texture(bmp, GL_LINEAR, GL_REPEAT);
	else
		textureObject = new tdogl::Texture(bmp);
}

void TextureQuad::Draw()
{
	shader->Enable();

	shader->SetUniformVar("mvp", matrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_QUADS, 0, 4);

	//unbind everything
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->Disable();
}

void TextureQuad::Draw(float x, float y)
{	
	shader->Enable();

	shader->SetUniformVar("mvp", matrix*glm::translate(glm::mat4(), glm::vec3(x, y, 0)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_QUADS, 0, 4);

	//unbind everything
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->Disable();
}

void TextureQuad::SetMatrix(glm::mat4 mvp)
{
	matrix = mvp;
}