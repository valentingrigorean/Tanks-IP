#include "Game.h"
#include "Utils.h"
#include <iostream>

Game::Game(Display * display, Input * input, GTimer* timer) :_display(display), _input(input), _timer(timer)
{
}

Game::~Game()
{
}

void Game::Init()
{
	_display->Init();

}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
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
		_display->SwapBuffers();
		if (_input->GetKey(G_KEY_ESCAPE))
			_state = GameState::GAME_EXIT;
		_input->PollEvents();
	}
}
