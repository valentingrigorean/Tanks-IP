#include "Display.h"
#include "GOpengl.h"

Display::Display(int width, int height, std::string & title):_width(width),_height(height),_title(title)
{

}

void Display::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

std::string Display::GetTitle() const
{
	return _title;
}

int Display::GetWidth() const
{
	return _width;
}

int Display::GetHeight() const
{
	return _height;
}

void Display::SetVSync(bool vsync)
{
	_vsync = vsync;
}

inline bool Display::GetVSync() const
{
	return _vsync;
}
