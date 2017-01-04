#pragma once
#include "Window.h"
#include "systems\ISystem.h"
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
		void showFPS();
	private:
		Window _window;
		double _lastTime;
		int _frames;
		std::vector<ISystem*> _systems;
	};
}