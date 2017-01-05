
#include "GWindow.h"
#include <functional>

std::map<GLFWwindow*, GWindow*> GWindow::CallbackMap;

GWindow::GWindow(int width, int height, std::string title) :_width(width), _height(height), _title(title)
{
}

GWindow::~GWindow()
{

}


bool GWindow::isFullscreen() const
{
	return _fullscreen;
}

void GWindow::setFullscreen(bool value)
{
	_fullscreen = value;
}

std::string GWindow::getTitle() const
{
	return _title;
}

void GWindow::init()
{
	if (_window != nullptr) return;

	if (glfwInit() == GLFW_FALSE)
		FATAL_ERROR("Failed to initialize glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(_width, _height, _title.c_str(), _fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	glfwMakeContextCurrent(_window);
	glfwSetWindowCloseCallback(_window, GWindow::internalCloseCallback);
	CallbackMap[_window] = this;

	glewExperimental = GL_TRUE;
	auto result = glewInit();
	if (glewInit() != GLEW_OK)
		FATAL_ERROR("Failed to initialize glew");
}

void GWindow::close()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
	glfwDestroyWindow(_window);
	glfwTerminate();
	CallbackMap.erase(_window);
}

void GWindow::setOnCloseCallback(OnCloseCallback callback)
{
	_onCloseCallback = callback;
}

void GWindow::swapBuffers()
{
	glfwSwapBuffers(_window);
}

void GWindow::internalCloseCallback(GLFWwindow * window)
{
	auto value = CallbackMap[window];
	if (value == nullptr) return;
	if (value->_onCloseCallback != nullptr)
		value->_onCloseCallback();
}
