#pragma once
#include "GOpengl.h"
#include <map>

class Texture2D
{
public:
	Texture2D();	

	void Dispose();

	GLuint GetId() const;

	GLuint GetWidth() const;
	GLuint GetHeight() const;	

	void Generate(GLuint width, GLuint height, unsigned char* data, GLint format = GL_RGBA);

	Texture2D & SetConfig(GLenum parameter, GLint value);

	GLint GetConfig(GLenum parameter);

	void Bind(int unit = 0) const;
	void UnBind() const;
private:	
	GLuint _id;
	GLuint _width;
	GLuint _height;
	std::map<GLenum, GLint> _paramMap;
};