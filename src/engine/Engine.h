#pragma once
#include "Window.h"
#include "ISystem.h"
#include <vector>

namespace tanks::engine
{
	class Engine
	{
	public:		
		Engine::~Engine();		
		void update(float dt);
		void mainLoop();
		void add(ISystem* system);
	private:
		void init();
	private:
		Window _window;
		std::vector<ISystem*> _systems;
	};
}