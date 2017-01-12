#pragma once
#include "Point.h"
#include "Size.h"

struct Rect
{
	float x;
	float y;
	int width;
	int height;
	
	Rect():Rect(0,0,0,0)
	{
	};

	Rect(int _x, int _y, int w, int h)
	{
		x = (float)x;
		y = (float)y;
		width =w;
		height = h;
	}

	Rect(Point p, Size s)
	{
		x = p.x;
		y = p.y;
		width = s.width;
		height = s.height;
	}

	float GetCenterX() const
	{
		return x + (width / 2.f);
	}

	float GetCenterY() const
	{
		return y + (height / 2.f);
	}

	// check if rects are intersected with AABB collision
	inline bool IsIntersected(Rect &rect2)
	{
		return x < rect2.x + rect2.width &&
			x + width > rect2.x &&
			y < rect2.y + rect2.height &&
			height + y > rect2.y;
	}
}; 