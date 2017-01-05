#pragma once

struct Color{
	float r;
	float b;
	float g;
	float a;
	Color() :r(0), b(0), g(0), a(1)
	{

	}

	Color(float _r, float _b, float _g) :Color(_r,_b,_g,1)
	{

	}

	Color(float _r, float _b, float _g, float _a) :r(_r),b(_b),g(_g),a(_a)
	{

	}


};

inline bool operator==(const Color& lhs, const Color& rhs) 
{
	return lhs.a == rhs.a && 
		lhs.r == rhs.r && 
		lhs.b == rhs.b && 
		lhs.g == rhs.g;
}

inline bool operator!=(const Color& lhs, const Color& rhs) 
{ 
	return !(lhs == rhs);
}