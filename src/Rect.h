#pragma once
#include "Point.h"
#include "Size.h"

struct Rect
{
	Point point;
	Size size;

	Rect() {};
	Rect(int x, int y, int w, int h)
	{
		point.x = (float)x;
		point.y = (float)y;
		size.width =w;
		size.height = h;
	}

	Rect(Point p, Size s)
	{
		point.x = p.x;
		point.y = p.y;
		size.width = s.width;
		size.height = s.height;
	}
}; 