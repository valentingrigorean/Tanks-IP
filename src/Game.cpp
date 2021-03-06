#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include <tank/components/SpriteComponent.h>
#include <tank/components/TransformComponent.h>
#include <tank/components/InputComponent.h>
#include <tank/components/BodyComponent.h>
#include <tank/ComponentsFactory.h>

#include <tank/Game.h>
#include <tank/Utils.h>
#include <tank/ResourceManager.h>
#include <tank/GRandom.h>

#include <tank/glfw/DebugDraw.h>

#include <tank/GConstants.h>


/// A typedef that is used to represent a second
typedef double Seconds;

/// \return The systems time now
inline Seconds GetTimeNow()
{
	using namespace std;
	return chrono::duration_cast<chrono::duration<Seconds>>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}


Game::Game(Display * display, Input * input) :
	_display(display),
	_input(input),
	_debugDrawSystem(_display->GetWidth(), _display->GetHeight())
{
	Init();
}

Game::~Game()
{
	delete _render;
	ResourceManager::Clear();
}

void Game::StartGame(LevelGame * lvlGame, GameStateSystem::IStateLisener * lisener)
{
	_levelGame = lvlGame;
	_gameStateLisener = lisener;
	_gameStateSystem.SetLevelGame(*lvlGame);
	InitSystems(_levelGame->EcsWorld(), _levelGame->PhysicsWorld());
	_isRunning = true;
	MainLoop();
}

void Game::Init()
{
	InitResources();

	auto projection = glm::ortho(0.0f, (float)_display->GetWidth(),
		(float)_display->GetHeight(), 0.f, -1.f, 1.f);

	auto shader = ResourceManager::GetShader("sprite");
	shader.Bind()
		.SetInteger("image", 0)
		.SetMatrix4f("projection", projection).UnBind();

	_render = new SpriteRender(shader);

	_renderSystem.SetRenderer(*_render);
	_inputSystem.SetInput(_input);
	_physicsSystem.SetListener(_collisionSystem);
	_gameStateSystem.SetStateLisener(*this);
}

void Game::Update(float dt)
{
	_levelGame->EcsWorld().refresh();

	_aiSystem.Update(dt);
	_inputSystem.Update();
	_gunControlSystem.Update(dt);
	_physicsSystem.Update(dt);
	_collisionSystem.Update();
	_bulletAgeSystem.Update(dt);
	_gameStateSystem.Update();
}

void Game::Render()
{
	_display->Clear();
	_renderSystem.Render();
	_debugDrawSystem.Render();
	_display->SwapBuffers();
}


void Game::MainLoop()
{
	const float MAX_FRAME_TIME = 1 / 4.f;
	const float DELTA_TIME = 1 / 60.f;
	Seconds currentTime = 0; // Holds the current time
	Seconds accumulator = 0; // Used to accumlate time in the game loop


	while (_isRunning)
	{
		_input->PollEvents();

		Seconds newTime = GetTimeNow();
		Seconds frameTime = newTime - currentTime;
		currentTime = newTime;

		// cap the loop delta time
		if (frameTime >= MAX_FRAME_TIME)
			frameTime = MAX_FRAME_TIME;

		accumulator += frameTime;

		// Update our game
		while (accumulator >= DELTA_TIME)
		{
			Update(DELTA_TIME); // update the game (with the constant delta time)
			accumulator -= DELTA_TIME; // decrease the accumulator
		}

		Render();
		if (_input->GetKey(G_KEY_ESCAPE))
			_isRunning = false;
		if (_input->GetKey(G_KEY_F8))
			_debugDrawSystem.EnableDebug(true);
		if (_input->GetKey(G_KEY_F7))
			_debugDrawSystem.EnableDebug(false);
	}
}

void Game::InitSystems(anax::World & world, b2World &pWorld)
{	
	_debugDrawSystem.SetWorld(&pWorld);
	_physicsSystem.SetPhysicsWorld(&pWorld);
	_collisionSystem.SetPWorld(&pWorld);
	world.removeAllSystems();
	world.addSystem(_renderSystem);
	world.addSystem(_inputSystem);
	world.addSystem(_physicsSystem);
	world.addSystem(_collisionSystem);
	world.addSystem(_gunControlSystem);
	world.addSystem(_bulletAgeSystem);
	world.addSystem(_aiSystem);
	world.addSystem(_gameStateSystem);
}

void Game::InitResources()
{
	ResourceManager::LoadShader(GetShaderPath("sprite.vert"), GetShaderPath("sprite.frag"), "sprite");

	ResourceManager::LoadTexture(GetTexturePath("background.png"), "bg");
	ResourceManager::LoadTexture(GetTexturePath("solid.png"), "s");
	ResourceManager::LoadTexture(GetTexturePath("brick.png"), "b");
	ResourceManager::LoadTexture(GetTexturePath("tank_h.png"), "tank_h");
	ResourceManager::LoadTexture(GetTexturePath("tank_s.png"), "tank_s");
	ResourceManager::LoadTexture(GetTexturePath("tank_d.png"), "tank_d");
	ResourceManager::LoadTexture(GetTexturePath("bullet.png"), "bullet");
}

void Game::GameEnded(GameObject * won)
{
	_isRunning = false;
	if (_gameStateLisener != nullptr)
		_gameStateLisener->GameEnded(won);
}
