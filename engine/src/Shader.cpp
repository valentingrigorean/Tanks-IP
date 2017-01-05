#include "Shader.h"

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
		printInfoLog(shader);
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
		printInfoLog(_program);
	}
	for (auto& shader : _shaders)
		glDetachShader(_program, shader);
	return *this;
}

void Shader::bind(GLuint location, float value)
{
	glGetAttribLocation(_program, "position");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Shader::bind(GLuint location, glm::mat4 const & matrix)
{

}

void Shader::use()
{
	glUseProgram(_program);
}

void Shader::unuse()
{
	glUseProgram(0);
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

void Shader::printInfoLog(GLuint id)
{
	GLint size;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
	auto buffer = new GLchar[size];
	glGetShaderInfoLog(id, size, nullptr, buffer);
	FATAL_ERROR(buffer);
	delete buffer;
}
