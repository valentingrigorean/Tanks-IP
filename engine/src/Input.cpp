#include "Input.h"


std::map<int, bool>  Input::KeyMap;

Input::Input()
{
}

Input::~Input()
{
}


bool Input::getKey(int keyCode)
{
	return KeyMap[keyCode];
}

bool Input::getKey(char key)
{
	return KeyMap[key];
}

void Input::pollEvents()
{
	glfwPollEvents();
}


void Input::registerWindow(GWindow* window)
{
	glfwSetKeyCallback(window->getContext(), Input::KeyCallback);
}

void Input::unregisterWindow(GWindow* window)
{
	glfwSetKeyCallback(window->getContext(), nullptr);
}


void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_RELEASE:
		KeyMap[key] = false;
		break;
	case GLFW_PRESS:
	case GLFW_REPEAT:
		KeyMap[key] = true;
		break;
	}
}
