#include <tank/graphics/Display.h>
#include <tank/graphics/GOpengl.h>

Display::Display(int width, int height, std::string & title):_width(width),_height(height),_title(title)
{

}

void Display::Clear()
{
	glClearColor(44/255.f, 41/255.f, 24/255.f, 1.0f);
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

bool Display::GetVSync() const
{
	return _vsync;
}
