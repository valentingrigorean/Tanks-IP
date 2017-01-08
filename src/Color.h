#pragma once

struct Color {

	Color();
	Color(int _r, int _g, int _b);

	Color(int _r, int _g, int _b, int _a);

	Color(float _r, float _g, float _b);

	Color(float _r, float _g, float _b, float _a);

	Color(const Color& color);


	float r;
	float b;
	float g;
	float a;

	static Color White;
	static Color Black;
	static Color Red;
	static Color Blue;
	static Color Green;
	static Color Yellow;
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