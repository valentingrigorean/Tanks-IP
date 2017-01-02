
#include "Window.h"

namespace tanks
{
	Window::Window(int width, int height, std::string title) :_width(width),_height(height), _title(title)
	{
	}

	Window::~Window()
	{
	}


	bool Window::is_fullscreen() const
	{
		return _fullscreen;
	}

	void Window::set_fullscreen(bool value)
	{
		_fullscreen = value;
	}

	void Window::init()
	{
		ASSERT(glfwInit() > 0, "failed to init opengl");


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		_window = glfwCreateWindow(_width, _height, _title.c_str(), _fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(_window, GL_TRUE);
		glfwTerminate();
	}
	GLFWwindow * Window::get_context() const
	{
		return _window;
	}
}