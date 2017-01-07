#include "Sprite.h"
#include "Sprite.h"
#include "Sprite.h"
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(Texture2D & texture)
{
	_texture = texture;
}

Texture2D& Sprite::GetTexture()
{
	return _texture;
}

glm::vec2 & Sprite::GetPosition()
{
	return _position;
}

glm::vec2 & Sprite::GetSize()
{
	return _size;
}

glm::vec3 & Sprite::GetColor()
{
	return _color;
}

float  Sprite::GetRotate()
{
	return _rotate;
}

void Sprite::SetRotate(GLfloat rotate)
{
	_rotate = rotate;
}

inline float  Sprite::GetScale()
{
	return _scale;
}

void Sprite::SetScale(GLfloat scale)
{
	if (scale < 0)
		scale = 0.f;
	if (scale > 1.0f)
		scale = 1.f;
	_scale = scale;
}

glm::mat4 Sprite::GetModel()
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(_position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5 * _size.y, 0.0f));
	model = glm::rotate(model, _rotate, glm::vec3(0.0, 0.0f, 1.0f));

	model = glm::scale(model, glm::vec3(_size, _scale));
	return model;
}
