#pragma once

#include "Display.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "LevelGame.h"

#include "systems/SpriteRenderingSystem.h"
#include "systems/InputSystem.h"
#include "systems/PhysicsSystem.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_EXIT
};

class Game: PhysicsSystem::ICollisionListener
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
	void OnCollisionOccured(CollisionHandler *collision);
	void LoadLevel(std::string levelPath);
private:
	GameState _state;
	Display *_display;
	Input *_input;
	SpriteRender *_render;

	SpriteRenderingSystem _renderSystem;
	InputSystem _inputSystem;
	PhysicsSystem _physicsSystem;
	LevelGame *_levelGame;
};