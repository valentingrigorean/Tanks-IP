#include "Shader.h"
#include "GError.h"
#include "io/GFile.h"

Shader::Shader()
{
	_id = glCreateProgram();
}

void Shader::Dispose()
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

	if (!CheckIfValid(shader, false))
		PrintInfoLog(shader, false);

	glAttachShader(_id, shader);
	glDeleteShader(shader);
	_shaders.push_back(shader);
	return *this;
}

Shader & Shader::Link()
{
	glLinkProgram(_id);
	if (!CheckIfValid(_id, true))
		PrintInfoLog(_id, true);
	for (auto& shader : _shaders)
		glDetachShader(_id, shader);
	_shaders.clear();
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
	return SetVector2f(name, value.x, value.y);	
}

Shader & Shader::SetVector2f(const char * name, Point & p)
{
	return SetVector2f(name, p.x, p.y);
}

Shader & Shader::SetVector3f(const char * name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(GetIdForName(name), x, y, z);
	return *this;
}

Shader & Shader::SetVector3f(const char * name, glm::vec3 & value)
{
	return SetVector3f(name, value.x, value.y, value.z);	
}

Shader & Shader::SetVector3f(const char * name, Color & value)
{
	return SetVector3f(name,value.r, value.g, value.g);
}

Shader & Shader::SetVector4f(const char * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(GetIdForName(name), x, y, z, w);
	return *this;
}

Shader & Shader::SetVector4f(const char * name, glm::vec4 & value)
{
	return SetVector4f(name, value.x, value.y, value.z, value.w);	
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

bool Shader::CheckIfValid(GLuint id, bool isProgram)
{
	GLint status = 0;
	if (isProgram)
		glGetProgramiv(id, GL_LINK_STATUS, &status);
	else
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

void Shader::PrintInfoLog(GLuint id, bool isProgram)
{
	GLint size;
	std::vector<char> buffer;
	switch (isProgram)
	{
	case true:
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &size);
		buffer.resize(size);
		glGetProgramInfoLog(id, size, nullptr, &buffer[0]);
		glDeleteProgram(id);
		break;
	case false:
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
		buffer.resize(size);
		glGetShaderInfoLog(id, size, nullptr, &buffer[0]);
		glDeleteShader(id);
		break;
	}
	FATAL_ERROR(&buffer[0]);
}
