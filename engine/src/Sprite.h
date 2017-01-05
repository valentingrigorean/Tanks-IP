#pragma once
#include "Gopengl.h"
#include "Texture.h"


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
