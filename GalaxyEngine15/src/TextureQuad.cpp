#include "..\include\TextureQuad.h"
#include "..\include\GlobalCustomVariables.h"

TextureQuad::TextureQuad(float w, float h, Material* _mat)
{
	// Set dimensions
	width = w; height = h;

	// Assign the material
	SetMaterial(_mat);
	Init();
}

TextureQuad::TextureQuad(void)
{

}

TextureQuad::~TextureQuad(void)
{
}

bool TextureQuad::Init()
{
	// Load shaders from program
	if (mat->GetShader()->IsReady())
	{
		glGenBuffers(1, &m_vbo);
		glGenVertexArrays(1, &m_vao);

		// bind the VAO
		glBindVertexArray(m_vao);

		// bind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		float uvMaxH = 1.0f;
		float uvMaxW = 1.0f;

		if (mat->isRepeating())
		{
			uvMaxW = width / mat->GetTextureDimentions().x;
			uvMaxH = height / mat->GetTextureDimentions().y;
		}

		// Set to full screen
		if (height == 0 && width == 0)
		{
			// Quad vertices
			GLfloat qdata[] = {
				0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top left
				1.0f, 0.0f, 0.0f, uvMaxW, 0.0f, // Top right
				1.0f, 1.0f, 0.0f, uvMaxW, uvMaxH, // Bottom right
				0.0f, 1.0f, 0.0f, 0.0f, uvMaxH  // Bottom left
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(qdata), qdata, GL_STATIC_DRAW);
		}
		else // probably ortho drawing
		{
			// Quad vertices
			GLfloat qdata[] = {
				0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top left
				width, 0.0f, 0.0f, uvMaxW, 0.0f, // Top right
				width, height, 0.0f, uvMaxW, uvMaxH, // Bottom right
				0.0f, height, 0.0f, 0.0f, uvMaxH  // Bottom left
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(qdata), qdata, GL_STATIC_DRAW);
		}

		// connect the xyz coords
		glEnableVertexAttribArray(mat->GetShader()->GetAttribLocation("vertex"));
		glVertexAttribPointer(mat->GetShader()->GetAttribLocation("vertex"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

		// connect the uv coords to the tex coords
		glEnableVertexAttribArray(mat->GetShader()->GetAttribLocation("uv"));
		glVertexAttribPointer(mat->GetShader()->GetAttribLocation("uv"), 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

		// unbind the VAO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Set origin to 0,0
		originX = 0; originY = height;

		return true;
	}
	else
	{
		LogError("Could not initialize the TextureQuad %p!\nMaterial %p:\n", this, mat);
		return false;
	}
}

// Not really using this anymore since the quad gets its texture object from the material... i'll keep it just in case
void TextureQuad::SetTexture(GLuint texture)
{
	m_texture = texture;
}

void TextureQuad::Draw()
{
	mat->GetShader()->Enable();

	mat->GetShader()->SetUniformVar("mvp", matrix*glm::translate(glm::mat4(), glm::vec3(originX, originY, 0)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mat->GetTexture()->object());

	glBindVertexArray(m_vao);
	glDrawArrays(GL_QUADS, 0, 4);

	//unbind everything
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mat->GetShader()->Disable();
}

void TextureQuad::Draw(float x, float y)
{	
	mat->GetShader()->Enable();

	mat->GetShader()->SetUniformVar("mvp", matrix*glm::translate(glm::mat4(), glm::vec3(x-originX, y-originY, 0)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mat->GetTexture()->object());

	glBindVertexArray(m_vao);
	glDrawArrays(GL_QUADS, 0, 4);

	//unbind everything
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mat->GetShader()->Disable();
}

void TextureQuad::Draw_f(float x, float y)
{
	x = ScreenWidth*x;
	y = ScreenHeight*y;

	Draw(x, y);
}

void TextureQuad::SetMaterial(Material* newMaterial)
{
	mat = newMaterial;
}

void TextureQuad::SetOrigin(float x, float y)
{
	originX = x; originY = height-y;
}

void TextureQuad::SetMatrix(glm::mat4 mvp)
{
	matrix = mvp;
}