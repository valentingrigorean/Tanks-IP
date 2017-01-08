#include "Transform2D.h"

Transform2D::Transform2D():_rotate(0),_scale(1.f)
{
}

Transform2D::Transform2D(Rect rect):_rect(rect),_rotate(0), _scale(1.f)
{
}

Transform2D::Transform2D(Point pos, Size size):Transform2D(Rect(pos,size))
{
}

Transform2D::Transform2D(float x, float y, float width,
	float height, float rotation, float scale):_rotate(rotation),_scale(scale)
{
	_rect.point.x = x;
	_rect.point.y = y;
	_rect.size.width = (int)width;
	_rect.size.height = (int)height;
}

Size & Transform2D::GetSize()
{
	return _rect.size;
}

void Transform2D::SetSize(Size & size)
{
	_rect.size = size;
}

Point & Transform2D::GetPosition()
{
	return _rect.point;
}

void Transform2D::SetPosition(Point & pos)
{
	_rect.point = pos;
}

float Transform2D::GetScale() const
{
	return _scale;
}

void Transform2D::SetScale(float scale)
{
	_scale = scale;
}

float Transform2D::GetRotate() const
{
	return _rotate;
}

void Transform2D::SetRotate(float rotate)
{
	_rotate = rotate;
}

glm::mat4 Transform2D::GetModel() const
{
	glm::mat4 model;
	auto offsetX = 0.5f * _rect.size.width;
	auto offsetY = 0.5f * _rect.size.height;
	model = glm::translate(model, glm::vec3(_rect.point.x,_rect.point.y, 0.0f));

	model = glm::translate(model, glm::vec3(offsetX, offsetY, 0.0f));
	model = glm::rotate(model, _rotate, glm::vec3(0.0, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-offsetX, -offsetY, 1.0f));

	model = glm::scale(model, glm::vec3(_rect.size.width,_rect.size.height, _scale));
	return model;
}
