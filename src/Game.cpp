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
	ResourceManager::Clear();
}

void Game::Init()
{
	_display->Init();

	auto projection = glm::ortho(0.0f, (float)_display->GetWidth(),
		(float)_display->GetHeight(), 0.f, -1.f, 1.f);

	auto shader = ResourceManager::LoadShader(
		GetShaderPath("sprite.vert").c_str(),
		GetShaderPath("sprite.frag").c_str(),
		"sprite").
		Bind().
		SetInteger("image", 0).
		SetMatrix4f("projection", projection);

	_render = new SpriteRender(shader);
	GRandom r;

	auto texture = ResourceManager::LoadTexture(GetTexturePath("sample.png").c_str(), "cat");
	for (int i = 0; i < 500; i++)
	{
		auto sprite = new Sprite(texture);
		sprite->GetSize().x = (float)r.Next(20,80);
		sprite->GetSize().y = (float)r.Next(20,80);
		sprite->GetPosition().x = (float)r.Next(0, _display->GetWidth());
		sprite->GetPosition().y = (float)r.Next(0, _display->GetHeight());
		sprite->GetColor().g = (float)r.NextDouble();
		sprite->GetColor().r = (float)r.NextDouble();
		sprite->GetColor().b = (float)r.NextDouble();
		sprite->SetRotate((float)r.Next(0,280));
		_spirtes.push_back(sprite);
	}
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
	for (auto sprite : _spirtes)
		_render->DrawSprite(*sprite);
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
		if (_input->GetKey('w'))
			for (auto sprite : _spirtes)
				sprite->GetPosition().y -= (50 * dtUpdate);
		if (_input->GetKey('s'))
			for (auto sprite : _spirtes)
				sprite->GetPosition().y += (50 * dtUpdate);
		if (_input->GetKey('a'))
			for (auto sprite : _spirtes)
				sprite->GetPosition().x -= (50 * dtUpdate);
		if (_input->GetKey('d'))
			for (auto sprite : _spirtes)
				sprite->GetPosition().x += (50 * dtUpdate);
		if (_input->GetKey('e'))
			for (auto sprite : _spirtes)
				sprite->SetRotate(sprite->GetRotate() + (1.f *dtUpdate));
		if (_input->GetKey('q'))
			for (auto sprite : _spirtes)
				sprite->SetRotate(sprite->GetRotate() - (1.f *dtUpdate));
	}
}
