#include "Shader.h"
#include "GError.h"
#include "io/GFile.h"

Shader::Shader()
{
	_id = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(_id);

}

GLuint Shader::GetId() const
{
	return _id;
}

Shader & Shader::AttachFile(const char * filePath)
{
	auto shader = GetProgramType(filePath);
	auto fileText = GFile::ReadAllText(filePath);
	auto text = (const GLchar *)fileText.c_str();
	return AttachSource(text, shader);
}

Shader & Shader::AttachSource(const char * sourceCode, GLenum type)
{
	auto shader = glCreateShader(type);
	glShaderSource(shader, 1, &sourceCode, nullptr);
	glCompileShader(shader);

	if (!CheckIfValid(shader, GL_COMPILE_STATUS, false))
	{
		glDeleteShader(shader);
		PrintInfoLog(shader, false);
	}
	glAttachShader(_id, shader);
	glDeleteShader(shader);
	_shaders.push_back(shader);
	return *this;
}

Shader & Shader::Link()
{
	glLinkProgram(_id);
	if (!CheckIfValid(_id, GL_LINK_STATUS, true))
	{
		glDeleteProgram(_id);
		PrintInfoLog(_id, true);
	}
	for (auto& shader : _shaders)
		glDetachShader(_id, shader);
	return *this;
}

Shader & Shader::Bind()
{
	glUseProgram(_id);
	return *this;
}

Shader & Shader::UnBind()
{
	glUseProgram(0);
	return *this;
}

Shader & Shader::SetFloat(const char * name, GLfloat value)
{
	glUniform1f(GetIdForName(name), value);
	return *this;
}

Shader & Shader::SetInteger(const char * name, GLint value)
{
	glUniform1i(GetIdForName(name), value);
	return *this;
}

Shader & Shader::SetVector2f(const char * name, GLfloat x, GLfloat y)
{
	glUniform2f(GetIdForName(name), x, y);
	return *this;
}

Shader & Shader::SetVector2f(const char * name, glm::vec2 & value)
{
	SetVector2f(name, value.x, value.y);
	return *this;
}

Shader & Shader::SetVector3f(const char * name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(GetIdForName(name), x, y, z);
	return *this;
}

Shader & Shader::SetVector3f(const char * name, glm::vec3 & value)
{
	SetVector3f(name, value.x, value.y, value.z);
	return *this;
}

Shader & Shader::SetVector4f(const char * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(GetIdForName(name), x, y, z, w);
	return *this;
}

Shader & Shader::SetVector4f(const char * name, glm::vec4 & value)
{
	SetVector4f(name, value.x, value.y, value.z, value.w);
	return *this;
}

Shader & Shader::SetMatrix4f(const char * name, glm::mat4 & value)
{
	glUniformMatrix4fv(GetIdForName(name), 1, GL_FALSE, glm::value_ptr(value));
	return *this;
}

inline GLint Shader::GetIdForName(const char * name)
{
	return glGetUniformLocation(_id, name);
}

GLenum Shader::GetProgramType(const char * filePath)
{
	auto ext = GFile::GetExtension(filePath);
	if (ext == ".vert")
		return GL_VERTEX_SHADER;
	if (ext == ".frag")
		return GL_FRAGMENT_SHADER;
	FATAL_ERROR("invalid shader program");
	return 0;
}

bool Shader::CheckIfValid(GLuint id, GLenum type, bool isProgram)
{
	GLint status;
	if (isProgram)
		glGetProgramiv(id, type, &status);
	else
		glGetShaderiv(id, type, &status);
	return status == GL_TRUE;
}

void Shader::PrintInfoLog(GLuint id, bool isProgram)
{
	GLint size;
	if (isProgram)
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &size);
	else
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
	auto buffer = new GLchar[size];
	glGetShaderInfoLog(id, size, nullptr, buffer);
	delete buffer;
	FATAL_ERROR(buffer);
}
