#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "components/SpriteComponent.h"
#include "components/TransformComponent.h"
#include "components/InputComponent.h"

#include "Game.h"
#include "Utils.h"
#include "ResourceManager.h"
#include "GRandom.h"


/// A typedef that is used to represent a second
typedef double Seconds;

/// \return The systems time now
inline Seconds GetTimeNow()
{
	using namespace std;
	return chrono::duration_cast<chrono::duration<Seconds>>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}


Game::Game(Display * display, Input * input) :_display(display), _input(input)
{
}

Game::~Game()
{
	delete _render;
	ResourceManager::Clear();
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
	_physicsSystem.SetListener(*this);
	LoadLevel("level1.txt");
}

void Game::Update(float dt)
{	
	_levelGame->EcsWorld().refresh();

	_inputSystem.Update();
	_physicsSystem.Update(dt);
}

void Game::Render()
{
	_display->Clear();
	_renderSystem.Render();
	_display->SwapBuffers();
}

void Game::LoadLevel(std::string levelPath)
{
	levelPath = GetLevelPath(levelPath.c_str());
	if (_levelGame != nullptr)
		delete _levelGame;
	_levelGame = LevelGame::LoadLevel(levelPath, _display->GetWidth(), _display->GetHeight());
	auto tank1 = _levelGame->GetTanks()[0];	
	tank1.addComponent<InputComponent>();
	tank1.activate();

	InitSystems(_levelGame->EcsWorld(),_levelGame->PhysicsWorld());
}

void Game::MainLoop()
{
	const float MAX_FRAME_TIME = 1 / 4.f;
	const float DELTA_TIME = 1 / 60.f;
	Seconds currentTime = 0; // Holds the current time
	Seconds accumulator = 0; // Used to accumlate time in the game loop


	while (_state != GameState::GAME_EXIT)
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
			_state = GameState::GAME_EXIT;
	}
}

void Game::InitSystems(anax::World & world,b2World &pWorld)
{
	_physicsSystem.SetPhysicsWorld(&pWorld);
	world.removeAllSystems();
	world.addSystem(_renderSystem);
	world.addSystem(_inputSystem);
	world.addSystem(_physicsSystem);	
}

void Game::InitResources()
{
	ResourceManager::LoadShader(GetShaderPath("sprite.vert"), GetShaderPath("sprite.frag"), "sprite");

	ResourceManager::LoadTexture(GetTexturePath("background.png"), "bg");
	ResourceManager::LoadTexture(GetTexturePath("solid1.png"), "s1");
	ResourceManager::LoadTexture(GetTexturePath("solid2.png"), "s2");
	ResourceManager::LoadTexture(GetTexturePath("brick1.png"), "b1");
	ResourceManager::LoadTexture(GetTexturePath("tank.png"), "t");
}

void Game::OnCollisionOccured(CollisionHandler * collision)
{

}