#pragma once
#include <glm\glm.hpp>
#include "Texture2D.h"
#include "Color.h"

class Sprite
{
public:
	Sprite();
	Sprite(Texture2D &texture);

	Texture2D& GetTexture();	
	void SetTexture(Texture2D &texture);

	Color& GetColor();
	void SetColor(Color& color);

	void SetFlipX(bool value);
	bool GetFlipX()const;

	void SetFlipY(bool value);
	bool GetFlipY()const;
private:
	bool _flipX;
	bool _flipY;
	Texture2D _texture;
	Color _color;
};