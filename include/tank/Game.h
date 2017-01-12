#pragma once

#include "graphics/Display.h"
#include "Input.h"
#include "graphics/SpriteRenderer.h"
#include "LevelGame.h"

#include "systems/SpriteRenderingSystem.h"
#include "systems/InputSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/GunControlSystem.h"


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
	void InitSystems(anax::World& world,b2World &pWorld);
	void InitResources();	
	void LoadLevel(std::string levelPath);
private:
	GameState _state;
	Display *_display;
	Input *_input;
	SpriteRender *_render;

	SpriteRenderingSystem _renderSystem;
	InputSystem _inputSystem;
	PhysicsSystem _physicsSystem;
	CollisionSystem _collisionSystem;
	GunControlSystem _gunControlSystem;

	LevelGame *_levelGame;
};