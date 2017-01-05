#include "Engine.h"
#include "Input.h"
#include "systems\RenderSystem.h"
#include "GTimer.h"
#include <sstream>


Engine::Engine(GWindow * window) :_window(window)
{
}

Engine::~Engine()
{
	Input::unregisterWindow(_window);
	_window->close();
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
	while (!glfwWindowShouldClose(_window->getContext()))
	{
		GTimer::update();
		//showFPS();
		update(GTimer::getDeltaTime());
		Input::pollEvents();
		if (Input::getKey(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(_window->getContext(), GL_TRUE);
	}
}

void Engine::add(ISystem * cSystem)
{
	_systems.push_back(cSystem);
}

void Engine::init()
{
	_window->init();
	Input::registerWindow(_window);
	add(new RenderSystem(_window));
	for (auto& cSystem : _systems)
		cSystem->init();
}

void Engine::showFPS()
{
	std::stringstream ss;
	ss << _window->getTitle() << "[" << GTimer::getFps() << " FPS]";
	glfwSetWindowTitle(_window->getContext(), ss.str().c_str());
}