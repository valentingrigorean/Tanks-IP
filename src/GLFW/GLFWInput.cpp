#include <ctype.h>

#include "GLFWInput.h"
#include "../GOpengl.h"

std::map<int, bool>  GLFWInput::KeysMap;
std::map<GLFWInput*, std::vector<GLFWwindow*>> GLFWInput::RegisterMap;

GLFWInput::GLFWInput():Input()
{
	RegisterMap.emplace(std::make_pair(this, std::vector<GLFWwindow*>()));
}

GLFWInput::~GLFWInput()
{
	auto it = RegisterMap.find(this);
	for (auto wIt : it->second)
		glfwSetKeyCallback(wIt, nullptr);
	RegisterMap.erase(this);
}

bool GLFWInput::GetKey(int keyCode)
{
	return KeysMap[keyCode];
}

bool GLFWInput::GetKey(char key)
{	
	return KeysMap[toupper(key)];
}

void GLFWInput::PollEvents()
{
	glfwPollEvents();
}

void GLFWInput::RegisterWindow(GLFWwindow * window)
{
	glfwSetKeyCallback(window, GLFWInput::KeyCallback);
	RegisterMap[this].push_back(window);
}

void GLFWInput::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{	
	switch (action)
	{
	case GLFW_RELEASE:
		KeysMap[key] = false;
		break;
	case GLFW_PRESS:
	case GLFW_REPEAT:
		KeysMap[key] = true;
		break;
	}
}
