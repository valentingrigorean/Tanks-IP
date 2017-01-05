#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{
	_program = glCreateProgram();
}


Shader::~Shader()
{
	glDeleteProgram(_program);
}

Shader& Shader::attach(const char * filePath)
{
	auto shader = create(filePath);
	auto fileText = GFile::readAllText(filePath);
	auto text = (const GLchar *)fileText.c_str();

	glShaderSource(shader, 1, &text, nullptr);
	glCompileShader(shader);

	if (!checkIfValid(shader, GL_COMPILE_STATUS, false))
	{
		glDeleteShader(shader);
		printInfoLog(shader,false);
	}

	glAttachShader(_program, shader);
	glDeleteShader(shader);
	_shaders.push_back(shader);
	return *this;
}

Shader & Shader::link()
{
	glLinkProgram(_program);
	if (!checkIfValid(_program, GL_LINK_STATUS, true))
	{
		glDeleteProgram(_program);
		printInfoLog(_program,true);
	}
	for (auto& shader : _shaders)
		glDetachShader(_program, shader);
	_shaders.clear();
	_wasLink = true;
	return *this;
}

GLuint Shader::get() const
{
	return _program;
}

Shader & Shader::bindAttribute(const char * name, int count, int size, void * offsetPointer)
{
	if (!_wasLink)
		FATAL_ERROR("You need to link before binding!");
	std::string loc(name);
	GLint position;

	auto attrPositionPair = _attributes.find(loc);

	if (attrPositionPair == _attributes.end())
	{
		position = glGetAttribLocation(_program, name);
		_attributes.emplace(std::make_pair(loc, position));
	}
	else
		position = attrPositionPair->second;
	glVertexAttribPointer(position, count, GL_FLOAT, GL_FALSE, size, offsetPointer);
	return *this;
}

Shader & Shader::bindUniform(const char * name, GLfloat val)
{
	auto location = glGetUniformLocation(_program, name);
	glUniform1f(location, val);
	return *this;
}

Shader & Shader::bindUniform(const char * name, const glm::vec2 & v)
{
	auto location = glGetUniformLocation(_program, name);
	glUniform2f(location, v.x, v.y);
	return *this;
}

Shader & Shader::bindUniform(const char * name, const glm::vec3 & v)
{
	auto location = glGetUniformLocation(_program, name);
	glUniform3f(location, v.r, v.b, v.g);
	return *this;
}

void Shader::use()
{
	
	glUseProgram(_program);
	for (auto& attribute : _attributes)
		glEnableVertexAttribArray(attribute.second);
}

void Shader::unuse()
{
	glUseProgram(0);
	for (auto& attribute : _attributes)
		glDisableVertexAttribArray(attribute.second);
}

GLuint Shader::create(const char * filePath)
{
	auto ext = GFile::getExtension(filePath);
	if (ext == ".vert")
		return glCreateShader(GL_VERTEX_SHADER);
	if (ext == ".frag")
		return glCreateShader(GL_FRAGMENT_SHADER);
	FATAL_ERROR("invalid shader program");
	return 0;
}

bool Shader::checkIfValid(GLuint id, GLenum type, bool isProgram = false)
{
	GLint status;
	if (isProgram)
		glGetProgramiv(id, type, &status);
	else
		glGetShaderiv(id, type, &status);
	return status == GL_TRUE;
}

void Shader::printInfoLog(GLuint id, bool isProgram)
{
	GLint size;
	if (isProgram)
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &size);
	else
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
	auto buffer = new GLchar[size];
	glGetShaderInfoLog(id, size, nullptr, buffer);
	FATAL_ERROR(buffer);
	delete buffer;
}
