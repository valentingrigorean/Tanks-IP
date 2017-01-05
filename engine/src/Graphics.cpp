#include "Graphics.h"
#include "GOpengl.h"

Graphics::Graphics(GWindow * window):_window(window),_clearColor(Color::Black)
{
}

Graphics::~Graphics()
{
	
}

void Graphics::init()
{
	_window->init();
}

Color Graphics::getClearColor() const
{
	return _clearColor;
}

void Graphics::setClearColor(Color color)
{
	_clearColor = color;
}

int Graphics::getWidth() const
{
	return _window->getWidth();
}

int Graphics::getHeight() const
{
	return _window->getHeight();
}

void Graphics::begin()
{
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::end()
{
	_window->swapBuffers();
}

GLFWwindow * Graphics::getContext() const
{
	return _window->getContext();
}
