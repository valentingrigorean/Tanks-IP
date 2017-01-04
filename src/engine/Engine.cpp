#include "Engine.h"
#include "Input.h"
#include <sstream>

namespace tanks::engine
{	

	void showFPS(GLFWwindow *pWindow);

	Engine::~Engine()
	{
		Input::unregisterWindow(&_window);
		_window.close();
	}

	void Engine::update(double dt)
	{
	}

	void Engine::mainLoop()
	{
		init();
		double previous = glfwGetTime();
		
		while (!glfwWindowShouldClose(_window.getContext()))
		{			
			double current = glfwGetTime();
			double elapsed = current - previous;
			previous = current;		
			update(elapsed);
			showFPS(_window.getContext());



			_window.swapBuffers();
			Input::pollEvents();
			if (Input::getKey(GLFW_KEY_ESCAPE))
				glfwSetWindowShouldClose(_window.getContext(), GL_TRUE);
		}
	}

	void Engine::add(ISystem * system)
	{
		
	}

	void Engine::init()
	{
		glewExperimental = GL_TRUE;
		glewInit();
		_window.init();
		Input::registerWindow(&_window);
	}

	int nbFrames = 0;
	double lastTime = 0;

	void showFPS(GLFWwindow *pWindow)
	{
		// Measure speed
		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;
		nbFrames++;
		if (delta >= 1.0) { // If last cout was more than 1 sec ago
			std::cout << 1000.0 / double(nbFrames) << std::endl;

			double fps = double(nbFrames) / delta;

			std::stringstream ss;
			ss << "TANKS" << " " << "1.0" << " [" << fps << " FPS]";

			glfwSetWindowTitle(pWindow, ss.str().c_str());

			nbFrames = 0;
			lastTime = currentTime;
		}
	}
}