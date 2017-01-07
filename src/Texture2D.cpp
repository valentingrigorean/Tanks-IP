#include "Texture2D.h"
#include "Utils.h"

Texture2D::Texture2D()
{
	_width = 0;
	_height = 0;
	glGenTextures(1, &_id);

	SetConfig(GL_TEXTURE_WRAP_S, GL_REPEAT);
	SetConfig(GL_TEXTURE_WRAP_T, GL_REPEAT);
	SetConfig(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	SetConfig(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_id);
}

GLuint Texture2D::GetId() const
{
	return _id;
}

GLuint Texture2D::GetWidth() const
{
	return _width;
}

GLuint Texture2D::GetHeight() const
{
	return _height;
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char * data,GLint format)
{
	_width = width;
	_height = height;

	glBindTexture(GL_TEXTURE_2D, _id);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	for (auto pair : _paramMap)
		glTexParameteri(GL_TEXTURE_2D, pair.first, pair.second);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D & Texture2D::SetConfig(GLenum parameter, GLint value)
{
	_paramMap[parameter] = value;
	return *this;
}

GLint Texture2D::GetConfig(GLenum parameter)
{
	return _paramMap[parameter];
}

void Texture2D::Bind(int unit) const
{
	unit = Clamp(unit,0, 32);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture2D::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, _id);
}
