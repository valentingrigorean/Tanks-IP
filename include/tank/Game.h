#pragma once

#include "graphics/Display.h"
#include "Input.h"
#include "graphics/SpriteRenderer.h"
#include "LevelGame.h"

#include "systems/SpriteRenderingSystem.h"
#include "systems/InputSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/CollisionSystem.h"


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
	void OnCollisionOccured(anax::Entity* e1, anax::Entity* e2);
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

	LevelGame *_levelGame;
};