#include "..\include\Material.h"

Material::Material(ShaderPair* s, const char* tex)
{
	shader = s; 
	s->Init();

	LoadTexture(tex);

	built = true;
}

Material::Material()
{

}

Material::~Material()
{
}

bool Material::BuildMaterial()
{
	shader->Init();

	return built = true;
}

void Material::SetShader(ShaderPair* s)
{
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

void Material::LoadTexture(const char* fn)
{
	// Load the texture object
	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(fn);
	bmp.flipVertically();

	textureObject = new tdogl::Texture(bmp);
}