#pragma once
#include <tank/Game.h>
#include <tank/glfw/GLFWInput.h>
#include <tank/glfw/GLFWDisplay.h>
#include <tank/systems/GameStateSystem.h>
#include <tank/LevelGame.h>
#include <tank/GRandom.h>
#include <iostream>

class ConsoleGUI :public GameStateSystem::IStateLisener
{
	enum MENU_SCREEN
	{
		SELECT_LEVEL,
		SELECT_PLAYER,
		SELECT_TANK,
		GAME
	};
public:
	ConsoleGUI();
	~ConsoleGUI();
	
	void ShowMenu();	
private:	
	void Reset();
	void ClearScreen();	
	void ShowLevelMenu();
	void ShowPlayerMenu();
	void ShowTankMenu();
	void SetAI();
	void SetAI(GameObject *obj);
	void GameEnded(GameObject *won);
private:
	MENU_SCREEN _currentScreen;
	GLFWDisplay _display;
	GLFWInput _input;
	Game *_game;
	LevelGame *_levelGame;
	GRandom _random;
	std::string _levelFile;
	int _players = 1;
};