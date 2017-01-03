#pragma once
#include "Window.h"

namespace tanks::engine
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void mainLoop();
	private:
		void init();
	private:
		Window _window;
	};
}