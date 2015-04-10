#pragma once
#include "..\stdafx.h"
#include <cassert>
#include <map>
#include <vector>
#include "video_includes.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

struct ShaderVaribale
{
	GLuint location;
	float  fValue;
	glm::mat4 mat;
};

class ShaderPair
{
public:
	ShaderPair(std::string vs, std::string fs);
	~ShaderPair(void);
	
	bool IsReady(){ return ready; }

	bool Init();

	void Enable();
	void Disable();

	void RegisterShaderVal(std::string varName, float val);
	void RegisterShaderVal(std::string varName, glm::mat4x4 val);

	void ModifyShaderVal(std::string varName, float val);
	void ModifyShaderVal(std::string varName, glm::mat4x4 val);

	GLint GetAttribLocation(const char* varName);

	void SetUniformVar(std::string varName, int val);
	void SetUniformVar(std::string varName, float val);
	void SetUniformVar(std::string varName, glm::mat4x4 val);
	void SetUniformVar(std::string varName, glm::mat3 val);
	void SetUniformVar(std::string varName, glm::vec2 val);
	void SetUniformVar(std::string varName, glm::vec3 val);
	void SetUniformVar(std::string varName, glm::vec4 val);

	GLuint GetUniformLocation(const char* varName);

	void PrintActiveUniforms();

private:

	bool Init(std::string vs, std::string fs);

	std::string vertexShaderDir, fragmentShaderDir;
	std::string shaderDir;

	GLuint scaleLocation;

	bool   AddShader(const char* fn, GLenum ShaderType);
	bool   LoadFromFile(const char* fn);

	GLuint program;
	bool ready, enabled;

	std::map<std::string, ShaderVaribale> shaderVars;
};

