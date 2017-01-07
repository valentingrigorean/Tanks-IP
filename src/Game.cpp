#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Utils.h"
#include "ResourceManager.h"


Game::Game(Display * display, Input * input, GTimer* timer) :_display(display), _input(input), _timer(timer)
{
}

Game::~Game()
{
	delete _render;
	delete _sprite;
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
		SetMatrix4f("projection",projection);

	_render = new SpriteRender(shader);
	
	auto texture = ResourceManager::LoadTexture(GetTexturePath("sample.png").c_str(), "cat");
	_sprite = new Sprite(texture);
	_sprite->GetSize().x = 200;
	_sprite->GetSize().y = 200;
	_sprite->GetPosition().x = 30;
	_sprite->GetPosition().y = 30;
	_sprite->GetColor().g = 1.f;
	_sprite->GetColor().r = 1.f;
	_sprite->GetColor().b = 1.f;
	_sprite->SetRotate(45.f);
	_sprite->GetColor().y = 1.f;
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
	_render->DrawSprite(*_sprite);
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
		Render();
		_input->PollEvents();
		if (_input->GetKey(G_KEY_ESCAPE))
			_state = GameState::GAME_EXIT;
		if (_input->GetKey('w'))
			_sprite->GetPosition().y -= 5;
		if (_input->GetKey('s'))
			_sprite->GetPosition().y += 5;
		if (_input->GetKey('a'))
			_sprite->GetPosition().x -= 5;
		if (_input->GetKey('d'))
			_sprite->GetPosition().x += 5;
		if (_input->GetKey('e'))
			_sprite->SetRotate(_sprite->GetRotate() + 0.05f);
		if (_input->GetKey('q'))
			_sprite->SetRotate(_sprite->GetRotate() - 0.05f);
	}
}
