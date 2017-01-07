#include "GLFWTimer.h"
#include <GLFW\glfw3.h>

GLFWTimer::GLFWTimer()
{
	LastFrame = glfwGetTime();
}

GLFWTimer::~GLFWTimer()
{

}

void GLFWTimer::Update()
{
	GTimer::Update();
	auto currentFrame = glfwGetTime();
	DeltaTime = (float)(currentFrame - LastFrame);
	LastFrame = currentFrame;
}

inline double GLFWTimer::StartTime()
{
	return  glfwGetTime();
}
