#include "Texture.h"
#include <soil\SOIL.h>


Texture::Texture()
{
	glGenTextures(1, &_id);

	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::~Texture()
{
	if (_id > 0)
		glDeleteTextures(1, &_id);
}

GLuint Texture::get() const
{
	return _id;
}

int Texture::getWidth() const
{
	return _width;
}

int Texture::getHeight() const
{
	return _height;
}

void Texture::loadTexture(const char * texturePath)
{
	glBindTexture(GL_TEXTURE_2D, _id);

	auto image = SOIL_load_image(texturePath, &_width, &_height, nullptr, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}
