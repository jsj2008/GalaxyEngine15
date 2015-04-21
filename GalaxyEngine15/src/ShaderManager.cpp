#include "..\include\ShaderManager.h"

std::vector<Shader> ShaderManager::shaders;


void ShaderManager::BuildShaders()
{
	for (size_t i = 0; i < shaders.size(); i++)
	{
		// Make a pointer to the shader
		Shader* s = &shaders[i];

		// Check if its been initalized, if not - init()
		if (!s->obj->IsReady())
			s->obj->Init();
	}
}

bool ShaderManager::AddShader(const char* fn, Shader_type st)
{
	// No repeats
	if (FindShader(st))
		return false;

	// Set up the shader object
	Shader s;

	// Set the shader members
	s.obj = new ShaderPair(fn);
	s.shaderType = st;

	shaders.push_back(s);
	
	return true;
}

ShaderPair* ShaderManager::GetShaderInstance(Shader_type st)
{
	Shader* s = FindShader(st);

	if (s)
		return s->obj;

	return NULL;
}

Shader* ShaderManager::FindShader(Shader_type st)
{
	for (size_t i = 0; i < shaders.size(); i++)
	{
		if (shaders[i].shaderType == st)
			return &shaders[i];
	}

	return NULL;
}

