#pragma once
#include "Display.h"
#include "Input.h"
#include "GTimer.h"
#include "SpriteRenderer.h"

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
	Game(Display *display,Input *input,GTimer* timer);
	~Game();

	void Init();
	void Update(float dt);
	void ProcessInput(float dt);
	void Render();
	void MainLoop();
private:
	GameState _state;
	Display *_display;
	Input *_input;
	GTimer *_timer;
	SpriteRender *_render;
	std::vector<Sprite*> _spirtes;	
};