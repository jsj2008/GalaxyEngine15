#include "..\include\Material.h"

Material::Material(ShaderPair* s, const char* tex) :textureRepeat(false), built(false)
{
	shader = s;			// Set shader object

	if (!shader->IsReady())
		shader->Init();			// and initialize it

	textureFileName = tex;
	LoadTexture(tex);	// Create the texture object

	built = true;		// Confirm that everything was built ok?>>
}

Material::Material()
{
	built = false;
}

Material::~Material()
{
}

bool Material::BuildMaterial()
{
	if (!shader->IsReady())
		shader->Init();

	return built = true;
}

void Material::SetShader(ShaderPair* s)
{
	// Update the shader object, must rebuild the material
	shader = s;
	built = false;
}

void Material::SetTexture(tdogl::Texture* tex)
{
	textureObject = tex;
}

void Material::SetTexture(const char* fileName)
{
	textureFileName = fileName;
	LoadTexture(textureFileName);
}

ShaderPair* Material::GetShader()
{
	return shader;
}

tdogl::Texture* Material::GetTexture()
{
	return textureObject;
}

bool Material::IsBuilt()
{
	return built;
}

void Material::SetRepeat(bool r)
{
	// Prevent a redundant texture reload
	if (r != textureRepeat)
	{
		textureRepeat = r;
		LoadTexture(textureFileName);
	}
}

bool Material::isRepeating()
{
	return textureRepeat;
}

Vector2f Material::GetTextureDimentions()
{
	return Vector2f(textureWidth, textureHeight);
}

void Material::LoadTexture(const char* fn)
{
	// Load the texture object
	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(fn);
	bmp.flipVertically();

	if (textureRepeat)
		textureObject = new tdogl::Texture(bmp, GL_LINEAR, GL_REPEAT);
	else
		textureObject = new tdogl::Texture(bmp);

	textureWidth = textureObject->originalWidth();
	textureHeight = textureObject->originalHeight();
}