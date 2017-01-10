#pragma once
#include <anax/World.hpp>

#include "Display.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "Factory.h"

#include "systems/SpriteRenderingSystem.h"
#include "systems/MovementSystem.h"
#include "systems/InputSystem.h"
#include "systems/CollisionSystem.h"


enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_EXIT
};

class Game: CollisionSystem::ICollisionListener
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
	void OnCollisionOccured(const anax::Entity & e1, const anax::Entity & e2);
private:
	GameState _state;
	Display *_display;
	Input *_input;
	SpriteRender *_render;

	SpriteRenderingSystem _renderSystem;
	InputSystem _inputSystem;
	MovementSystem _moveSystem;
	CollisionSystem _collisionSystem;

	anax::World _world;
};