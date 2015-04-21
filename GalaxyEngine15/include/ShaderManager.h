#pragma once
#include "ShaderPair.h"

enum Shader_type
{
	SHADER_UV_TEXTURE
};

struct Shader
{
	Shader_type shaderType;
	ShaderPair* obj;
};

class ShaderManager
{
public:


	static void BuildShaders();

	static bool AddShader(const char* fn, Shader_type st);

	static ShaderPair* GetShaderInstance(Shader_type st);

private:
	static Shader* FindShader(Shader_type st);
	static std::vector<Shader> shaders;			// Compiled shaders
};

