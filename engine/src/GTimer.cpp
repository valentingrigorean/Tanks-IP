#include "GTimer.h"
#include <GLFW\glfw3.h>

double GTimer::_lastTime;
double GTimer::_previews;
int GTimer::_frames;
float GTimer::_delta;

void GTimer::update()
{
	double current = glfwGetTime();
	_delta = current - _previews;
	_previews = current;
}

float GTimer::getDeltaTime()
{
	if (_delta < 0 || _delta > 1)
		_delta = 0.025;
	return _delta;
}

float GTimer::getFps()
{
	return glfwGetTimerFrequency();
}

GTimer::GTimer()
{
	_previews = glfwGetTime();
}
