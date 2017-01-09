#include "Sprite.h"
#include "Sprite.h"
#include "Sprite.h"
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite():_color(1.f,1.f,1.f,1.f)
{
}

Sprite::Sprite(Texture2D & texture):Sprite()
{
	_texture = texture;
}

Texture2D& Sprite::GetTexture()
{
	return _texture;
}

void Sprite::SetTexture(Texture2D & texture)
{
	_texture = texture;
}

Color & Sprite::GetColor()
{
	return _color;
}

void Sprite::SetColor(Color & color)
{
	_color = color;
}

void Sprite::SetFlipX(bool value)
{
	_flipX = value;
}

bool Sprite::GetFlipX() const
{
	return _flipX;
}

void Sprite::SetFlipY(bool value)
{
	_flipY = value;
}

bool Sprite::GetFlipY() const
{
	return _flipY;
}
