#pragma once
#include "ShaderPair.h"
#include "Texture.h"
#include "math_3d.h"

/*
Material
----------------------------------------------
Can be applied to a quad or any other shape.
*/

class Material
{
public:
	Material();
	Material(ShaderPair* s, const char* tex);
	~Material();

	bool BuildMaterial();

	void SetShader(ShaderPair* s);

	void SetTexture(tdogl::Texture* tex);
	void SetTexture(const char* fileName);

	void LoadTexture(const char* fn);

	ShaderPair*     GetShader();
	tdogl::Texture* GetTexture();

	bool IsBuilt();

	// Texture settings
	void SetRepeat(bool r);

	bool isRepeating();

	Vector2f GetTextureDimentions();

private:

	bool built, textureRepeat;
	float textureWidth, textureHeight;

	// Materials are made up of a texture and a shader
	// ----------------------------------------------	
	ShaderPair* shader;					// Shader pair (vertex and fragment)

	const char* textureFileName;		// Texture file name
	tdogl::Texture* textureObject;		// Texture object
};

