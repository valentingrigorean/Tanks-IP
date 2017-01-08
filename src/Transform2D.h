#pragma once
#include "Rect.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform2D
{
public:
	Transform2D();
	Transform2D(Rect rect);
	Transform2D(Point pos,Size size);
	Transform2D(float x, float y, float width, float height,
		float rotation = 0.f, float scale = 1.f);
	
	Size& GetSize();
	Point& GetPosition();

	float GetScale() const;
	void SetScale(float scale);

	float GetRotate() const;
	void SetRotate(float rotate);

	glm::mat4 GetModel() const;
private:
	Rect _rect;
	float _rotate;
	float _scale;
};