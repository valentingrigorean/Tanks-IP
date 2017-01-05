#pragma once
#include "GWindow.h"
#include "systems\ISystem.h"
#include <vector>


class Engine
{
public:
	Engine(GWindow *window);
	Engine::~Engine();
	void update(float dt);
	void mainLoop();
	void add(ISystem* system);
private:
	void init();
	void showFPS();
private:
	GWindow* _window;
	std::vector<ISystem*> _systems;
};
