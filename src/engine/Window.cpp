
#include "Window.h"
#include <functional>

namespace tanks::engine
{
	std::map<GLFWwindow*, Window*> Window::CallbackMap;

	Window::Window(int width, int height, std::string title) :_width(width),_height(height), _title(title)
	{
	}

	Window::~Window()
	{
		
	}


	bool Window::isFullscreen() const
	{
		return _fullscreen;
	}

	void Window::setFullscreen(bool value)
	{
		_fullscreen = value;
	}

	void Window::init()
	{
		if (_window != nullptr) return;
		
		ASSERT(glfwInit() > 0, "failed to init opengl");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		_window = glfwCreateWindow(_width, _height, _title.c_str(), _fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);		
		glfwMakeContextCurrent(_window);		
		glfwSetWindowCloseCallback(_window, Window::internalCloseCallback);
		CallbackMap[_window] = this;
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(_window, GL_TRUE);
		glfwDestroyWindow(_window);
		glfwTerminate();
		CallbackMap.erase(_window);
	}

	void Window::setOnCloseCallback(OnCloseCallback callback)
	{
		_onCloseCallback = callback;
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(_window);
	}

	void Window::internalCloseCallback(GLFWwindow * window)
	{
		auto value = CallbackMap[window];
		if (value == nullptr) return;
		if (value->_onCloseCallback != nullptr)
			value->_onCloseCallback();
	}
}