#include "color.h"


Color Color::Red(255, 0, 0);
Color Color::Blue(0, 255, 0);
Color Color::Green(0, 0, 255);
Color Color::Yellow(255, 255, 0);
Color Color::Black(0, 0, 0);
Color Color::White(255, 255,255);

Color::Color():r(0), g(0), b(0), a(1)
{

}

Color::Color(int _r, int _g, int _b) :Color(_r, _g, _b, 255)
{
}

Color::Color(int _r, int _g, int _b, int _a) :r(_r / 255.f), g(_g / 255.f), b(_b / 255.f), a(_a / 255.f)
{
}

Color::Color(float _r, float _g, float _b) :Color(_r, _g, _b, 1.f)
{

}

Color::Color(float _r, float _g, float _b, float _a) :r(_r), g(_g), b(_b), a(_a)
{

}

Color::Color(const Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}
