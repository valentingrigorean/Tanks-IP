#include "Sprite.h"

namespace tanks::engine
{

	Sprite::Sprite()
	{
	
	}

	Sprite::~Sprite()
	{
	}

	Texture& Sprite::getTexture() 
	{		
		return _texture;
	}

	void Sprite::loadImage(const char * fileName)
	{
		
	}
}