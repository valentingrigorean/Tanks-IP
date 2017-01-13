#pragma once

struct Point
{
	float x;
	float y;

	Point():Point(0.f,0.f)
	{
	};
	Point(float _x, float _y) :x(_x), y(_y) {};
};