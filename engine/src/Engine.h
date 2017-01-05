#pragma once
#include "GWindow.h"
#include "systems\ISystem.h"
#include <vector>
#include "Graphics.h"

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
	Graphics* _graphics;
	std::vector<ISystem*> _systems;
};
