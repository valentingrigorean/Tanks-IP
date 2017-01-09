#pragma once
#include "Point.h"
#include "Size.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform2D
{
public:
	Transform2D();	
	Transform2D(Point pos,Size size);
	Transform2D(float x, float y, float width, float height,
		float rotation = 0.f, float scale = 1.f);
	
	Size& GetSize();
	void SetSize(Size &size);

	Point& GetPosition();
	void SetPosition(Point &pos);

	float GetScale() const;
	void SetScale(float scale);

	float GetRotate() const;
	void SetRotate(float rotate);

	void Move(float x, float y);

	glm::mat4 GetModel() const;
private:
	Size _size;
	Point _position;
	float _rotate;
	float _scale;
};