#pragma once
#include "GWindow.h"
#include "color.h"

class Graphics
{
public:
	Graphics(GWindow * window);
	~Graphics();

	void init();

	Color getClearColor() const;
	void setClearColor(Color color);

	int getWidth()const;
	int getHeight()const;

	void begin();
	void end();

	GLFWwindow* getContext() const;

private:
	GWindow* _window;
	Color _clearColor;
	int _width;
	int _height;
};