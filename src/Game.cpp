#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Utils.h"
#include "ResourceManager.h"
#include "GRandom.h"


Game::Game(Display * display, Input * input, GTimer* timer) :_display(display), _input(input), _timer(timer)
{
}

Game::~Game()
{
	delete _render;
	for (auto it : _spirtes)
		delete it;
	delete _background;
	ResourceManager::Clear();
}

void Game::Init()
{
	_display->Init();

	auto projection = glm::ortho(0.0f, (float)_display->GetWidth(),
		(float)_display->GetHeight(), 0.f, -1.f, 1.f);

	auto shader = ResourceManager::LoadShader(
		GetShaderPath("sprite.vert"),
		GetShaderPath("sprite.frag"),
		"sprite").
		Bind().
		SetInteger("image", 0).
		SetMatrix4f("projection", projection);

	_render = new SpriteRender(shader);

	//Load textures
	ResourceManager::LoadTexture(GetTexturePath("background.png"), "bg");
	ResourceManager::LoadTexture(GetTexturePath("solid1.png"), "s1");
	ResourceManager::LoadTexture(GetTexturePath("solid2.png"), "s2");
	ResourceManager::LoadTexture(GetTexturePath("brick1"), "b1");

	_background = new GameObject(
		Point(0.f,0.f),
		Size(_display->GetWidth(), _display->GetHeight()),
		ResourceManager::GetTexture(std::string("bg")));
	
}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
	_display->Clear();
	_render->DrawSprite(_background->GetSprite(), _background->GetTransform());
	_display->SwapBuffers();
}

void Game::MainLoop()
{
	double lastFrame = _timer->StartTime();
	while (_state != GameState::GAME_EXIT)
	{
		_timer->Update();
		auto dt = _timer->StartTime() - lastFrame;
		if (dt >= 1.0)
		{
			_display->SetTitle(Convert(_timer->GetFps()));
			lastFrame = _timer->StartTime();
		}
		auto dtUpdate = _timer->GetDeltaTime();
		Render();
		_input->PollEvents();		

		if (_input->GetKey(G_KEY_ESCAPE))
			_state = GameState::GAME_EXIT;
	}
}
