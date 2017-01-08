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
