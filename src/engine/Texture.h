#pragma once
#include <string>
#include "opengl.h"

namespace tanks::engine
{

	class Texture
	{
	public:
		Texture();
		~Texture();

		GLuint get() const;

		int getWidth() const;
		int getHeight() const;

		void loadTexture(const char* texturePath);
	private:
		GLuint _id;
		int _width;
		int _height;
		std::string _texturePath;
	};

}

