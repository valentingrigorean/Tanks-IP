#include <tank/graphics/Transform2D.h>

Transform2D::Transform2D():_rotate(0),_scale(1.f),_offset(0,0)
{
}


Transform2D::Transform2D(Point pos, Size size):_position(pos),_size(size), _offset(0, 0)
{
}

Transform2D::Transform2D(float x, float y, float width,
	float height, float rotation, float scale):_rotate(rotation),_scale(scale), _offset(0, 0)
{
	_position.x = x;
	_position.y = y;
	_size.width = (int)width;
	_size.height = (int)height;
}

Size & Transform2D::GetSize()
{
	return _size;
}

void Transform2D::SetSize(Size & size)
{
	_size = size;
}

Point & Transform2D::GetPosition()
{
	return _position;
}

void Transform2D::SetPosition(float x,float y)
{
	_position.x = x;
	_position.y = y;
}

void Transform2D::SetPosition(Point & pos)
{
	_position = pos;
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

void Transform2D::SetOffset(Point offset)
{
	_offset = offset;
}

Point & Transform2D::GetOffset()
{
	return _offset;
}

void Transform2D::Move(float x, float y)
{
	_position.x += x;
	_position.y += y;
}

glm::mat4 Transform2D::GetModel() const
{
	glm::mat4 model;
	auto offsetX = 0.5f * _size.width;
	auto offsetY = 0.5f * _size.height;
	
	model = glm::translate(model, glm::vec3(_position.x + _offset.x,_position.y + _offset.y, 0.0f));

	model = glm::translate(model, glm::vec3(offsetX, offsetY, 0.0f));
	model = glm::rotate(model, glm::radians(_rotate), glm::vec3(0.0, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-offsetX, -offsetY, 1.0f));

	model = glm::scale(model, glm::vec3(_size.width,_size.height, _scale));
	return model;
}