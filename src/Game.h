#pragma once
#include <anax/World.hpp>

#include "Display.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "Factory.h"
#include "systems/SpriteRenderingSystem.h"
#include "systems/MovementSystem.h"


enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_EXIT
};

class Game
{
public:
	Game(Display *display,Input *input);
	~Game();

	void Init();
	void Update(float dt);	
	void Render();
	void MainLoop();
private:
	void InitResources();
private:
	GameState _state;
	Display *_display;
	Input *_input;
	SpriteRender *_render;
	SpriteRenderingSystem _renderSystem;

	anax::World _world;
};