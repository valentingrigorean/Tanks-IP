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
#include "systems/BulletAgeSystem.h"
#include "systems/DebugDrawSystem.h"
#include "systems/AISystem.h"
#include "systems/GameStateSystem.h"


class Game: GameStateSystem::IStateLisener
{
public:
	Game(Display *display,Input *input);
	~Game();
	
	void StartGame(LevelGame *lvlGame,GameStateSystem::IStateLisener *lisener);
private:
	void Init();
	void Update(float dt);
	void Render();
	void MainLoop();
	void InitSystems(anax::World& world,b2World &pWorld);
	void InitResources();
	void GameEnded(GameObject *won);
private:
	bool _isRunning;
	GameStateSystem::IStateLisener *_gameStateLisener;

	Display *_display;
	Input *_input;
	SpriteRender *_render;

	SpriteRenderingSystem _renderSystem;
	InputSystem _inputSystem;
	PhysicsSystem _physicsSystem;
	CollisionSystem _collisionSystem;
	GunControlSystem _gunControlSystem;
	BulletAgeSystem _bulletAgeSystem;
	DebugDrawSystem _debugDrawSystem;
	AISystem _aiSystem;
	GameStateSystem _gameStateSystem;

	LevelGame *_levelGame;
};