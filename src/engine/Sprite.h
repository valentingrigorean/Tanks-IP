#pragma once
#include "opengl.h"
#include "Texture.h"

namespace tanks::engine
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();	

		Texture& getTexture();

		void loadImage(const char* path);
	private:		
		Texture _texture;
	};
}