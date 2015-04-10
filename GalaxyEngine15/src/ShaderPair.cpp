#include "..\include\ShaderPair.h"
#include "..\include\logger.h"


ShaderPair::ShaderPair(std::string vs, std::string fs) : ready(false), shaderDir("../res/shaders/"){ vertexShaderDir = vs; fragmentShaderDir = fs; }
ShaderPair::~ShaderPair(void){}

bool ShaderPair::Init()
{
	return Init(vertexShaderDir, fragmentShaderDir);
}

bool ShaderPair::Init(std::string vs, std::string fs)
{
	int errorCode = 0;
	// Create the program
	program = glCreateProgram();

	// Add the shaders
	if(!AddShader(vs.c_str(), GL_VERTEX_SHADER))
		return false;

	if(!AddShader(fs.c_str(), GL_FRAGMENT_SHADER))
		return false;

	// Link and compile the program, check for errors
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &errorCode);

	// Handle errors
	if(errorCode == GL_FALSE)
	{
		int length = 0;
		char* buff = NULL;

		// Get log length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		// Clear errors
		buff = new char[length];

		glGetProgramInfoLog(program, length, &length, buff);
		glDeleteProgram(program);

		LogError("Error linking shaders: ", buff);

		delete[] buff;

		return false;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &errorCode);
	if(!errorCode)
	{

		int length = 0;
		char* buff = NULL;

		// Get log length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		// Clear errors
		buff = new char[length];

		glGetProgramInfoLog(program, length, &length, buff);
		glDeleteProgram(program);

		LogError("Error validating shaders: %s", buff);

		delete[] buff;

		ready = true;

		return false;
	}
	
	std::string strMessage = "Successfully compiled: ";
	strMessage += vs;
	strMessage += "/";
	strMessage += fs;
	strMessage += "\n";

	LogMessage(strMessage.c_str());

	return (ready=true);
}

bool ShaderPair::AddShader(const char* fn, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		LogError("Cannot create shader", (char*)ShaderType);
	}

	std::ifstream	file;
	std::string		source, line;

	std::string strLoc = shaderDir + fn;

	file.open(strLoc);
	if(!file.is_open())
	{
		std::string err = "File does not exist - ";
		err+=fn;
		LogError("Shader loader:", err);
		return false;
	}

	while(std::getline(file, line))
	{
		source += line + "\n";
	}

	file.close();

	const GLchar* p[1];
	p[0] = source.c_str();

	GLint Lengths[1];
	Lengths[0]= strlen(source.c_str());

	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);

	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	int	length;

	if (!success) {

		char* buff = NULL;

		// Get log length
		glGetShaderiv(ShaderObj, GL_INFO_LOG_LENGTH, &length);

		// Clear errors
		buff = new char[length];

		glGetShaderInfoLog(ShaderObj, length, &length, buff);
		glDeleteShader(ShaderObj);

		LogError("Compile shader error: %s", buff);

		delete[] buff;

		return false;
	}

	glAttachShader(program, ShaderObj);

	return true;
}

void ShaderPair::Enable()
{
	if(ready)
	{
		glUseProgram(program);
	}
}

void ShaderPair::Disable()
{
	glUseProgram(0);
	enabled = false;
}

GLuint ShaderPair::GetUniformLocation(const char* varName)
{
	GLuint asint;

	asint = glGetUniformLocation(program, varName);
	if(asint == 0xFFFFFFFF)
	{		
		LogError("Could not get UniformLocation of %s\n", varName);
		PrintActiveUniforms();
		assert(asint != 0xFFFFFFFF);
	}

	return asint;
}

void ShaderPair::RegisterShaderVal(std::string varName, float val)
{
	ShaderVaribale sv;

	sv.fValue = val;
	sv.location = GetUniformLocation(varName.c_str());

	shaderVars[varName] = sv;

	glUniform1f(sv.location, val);
}

void ShaderPair::SetUniformVar(std::string varName, int val)
{
	glUniform1i(GetUniformLocation(varName.c_str()), val);
}

void ShaderPair::SetUniformVar(std::string varName, float val)
{
	glUniform1f(GetUniformLocation(varName.c_str()), val);
}

void ShaderPair::SetUniformVar(std::string varName, glm::vec3 val)
{
	glUniform3fv(GetUniformLocation(varName.c_str()), 1, glm::value_ptr(val));
}

void ShaderPair::SetUniformVar(std::string varName, glm::vec2 val)
{
	glUniform2fv(GetUniformLocation(varName.c_str()), 1, glm::value_ptr(val));
}

void ShaderPair::SetUniformVar(std::string varName, glm::vec4 val)
{
	glUniform4fv(GetUniformLocation(varName.c_str()), 1, glm::value_ptr(val));
}

void ShaderPair::SetUniformVar(std::string varName, glm::mat4 val)
{
	glUniformMatrix4fv(GetUniformLocation(varName.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void ShaderPair::SetUniformVar(std::string varName, glm::mat3 val)
{
	glUniformMatrix3fv(GetUniformLocation(varName.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void ShaderPair::RegisterShaderVal(std::string varName, glm::mat4 val)
{
	ShaderVaribale sv;

	sv.mat = val;
	sv.location = GetUniformLocation(varName.c_str());

	shaderVars[varName] = sv;

	glUniformMatrix4fv(sv.location, 1, GL_FALSE, glm::value_ptr(val));
}

void ShaderPair::ModifyShaderVal(std::string varName, float val)
{
	shaderVars[varName].fValue = val;
	glUniform1f(shaderVars[varName].location, val);
}

void ShaderPair::ModifyShaderVal(std::string varName, glm::mat4 val)
{
	shaderVars[varName].mat = val;
	glUniformMatrix4fv(shaderVars[varName].location, 1, GL_FALSE, glm::value_ptr(shaderVars[varName].mat));
}

GLint ShaderPair::GetAttribLocation(const char* varName)
{
	if(!varName)
		LogError("varName was NULL!\n");

	GLint attrib = glGetAttribLocation(program, varName);
	if(attrib == -1)
		LogError("Program attribute not found: %s\n",varName);

	return attrib;
}

void ShaderPair::PrintActiveUniforms()
{
	if(ready)
	{
		GLint numUniforms;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniforms);
			
		if(numUniforms > 0)
		{
			std::vector<std::string> nameList;
			nameList.reserve(numUniforms);

			for(int i = 0; i < numUniforms; ++i)
			{
				GLchar name[64];
				GLint  len;
				glGetActiveUniformName(program, i, 64, &len, &name[0]);

				nameList.push_back(std::string(name));
			}

			LogMessage("\nCurrent active Uniform variables in program:\n");

			for(size_t i = 0; i < nameList.size(); i++)
			{
				LogError("%s\n",nameList[i].c_str());
			}
		}
	}
}