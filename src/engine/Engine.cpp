#include "Engine.h"
#include "Input.h"
#include "systems\RenderSystem.h"
#include <sstream>

namespace tanks::engine
{	
	Engine::~Engine()
	{
		Input::unregisterWindow(&_window);
		_window.close();
		for (auto& cSystem : _systems)
			delete cSystem;
	}

	void Engine::update(float dt)
	{
		for (auto& cSystem : _systems)
			cSystem->update(dt);
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
			showFPS();
			_window.swapBuffers();
			Input::pollEvents();
			if (Input::getKey(GLFW_KEY_ESCAPE))
				glfwSetWindowShouldClose(_window.getContext(), GL_TRUE);
		}
	}

	void Engine::add(ISystem * cSystem)
	{
		_systems.push_back(cSystem);
	}

	void Engine::init()
	{		
		_window.init();
		Input::registerWindow(&_window);
		add(new RenderSystem());
		for (auto& cSystem : _systems)
			cSystem->init();
	}

	void Engine::showFPS()
	{		
		double currentTime = glfwGetTime();
		double delta = currentTime - _lastTime;
		_frames++;
		if (delta >= 1.0) { // If last cout was more than 1 sec ago
			std::cout << 1000.0 / double(_frames) << std::endl;

			double fps = double(_frames) / delta;

			std::stringstream ss;
			ss << "TANKS" << " " << "1.0" << " [" << fps << " FPS]";

			glfwSetWindowTitle(_window.getContext(), ss.str().c_str());

			_frames = 0;
			_lastTime = currentTime;
		}
	}

	
}