#include "Engine.h"
#include "Input.h"

namespace tanks::engine
{

	Engine::Engine()
	{
	}


	Engine::~Engine()
	{
		Input::unregisterWindow(&_window);
		_window.close();
	}

	void Engine::mainLoop()
	{
		init();
		int frames = 0;
		while (!glfwWindowShouldClose(_window.getContext()))
		{			
			Input::pollEvents();
			if (Input::getKey(GLFW_KEY_ESCAPE))
				glfwSetWindowShouldClose(_window.getContext(), GL_TRUE);
			frames++;
			if(frames % 1000  == 0)
			std::cout << "Frames:" << frames <<std::endl;
		}
	}

	void Engine::init()
	{
		_window.init();
		Input::registerWindow(&_window);
	}

}