#include "Engine.h"
#include "Input.h"


namespace tanks::engine
{	

	Engine::~Engine()
	{
		Input::unregisterWindow(&_window);
		_window.close();
	}

	void Engine::update(float dt)
	{
	}

	//implementation from http://gameprogrammingpatterns.com/game-loop.html
	void Engine::mainLoop()
	{
		init();
		double previous = glfwGetTime();
		double lag = 0;
		double MS_PER_UPDATE = 1 / 60.0;
		while (!glfwWindowShouldClose(_window.getContext()))
		{			
			double current = glfwGetTime();
			double elapsed = current - previous;
			previous = current;
			lag += elapsed;
			
			while (lag >= MS_PER_UPDATE)
			{
				update(lag / MS_PER_UPDATE);
				lag -= MS_PER_UPDATE;
			}
			
			update(lag / MS_PER_UPDATE);
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
		_window.init();
		Input::registerWindow(&_window);
	}

}