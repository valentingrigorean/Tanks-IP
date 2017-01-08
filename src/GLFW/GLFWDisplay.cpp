#include "GLFWDisplay.h"
#include "../GError.h"

GLFWDisplay::GLFWDisplay(int width, int height, std::string & title) :Display(width, height, title)
{
	
}

GLFWDisplay::~GLFWDisplay()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void GLFWDisplay::Init()
{
	if (_window != nullptr) return;
	if (glfwInit() == GLFW_FALSE)
		FATAL_ERROR("Failed to initialize glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	
	_window = glfwCreateWindow(GetWidth(), GetHeight(), GetTitle().c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(_window);

	glViewport(0, 0, GetWidth(), GetHeight());
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		FATAL_ERROR("Failed to initialize glew");

	glfwSwapInterval(0);
#if DEBUG
	std::cout << "OpenGL " << glGetString(GL_VERSION) << " ,GLSL "
		<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif
}

void GLFWDisplay::SwapBuffers()
{
	glfwSwapBuffers(_window);	
}

void GLFWDisplay::SetTitle(std::string & title)
{
	glfwSetWindowTitle(_window, title.c_str());
}

GLFWwindow * GLFWDisplay::GetNativeWindow()
{
	return _window;
}
