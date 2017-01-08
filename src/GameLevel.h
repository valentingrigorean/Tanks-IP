#pragma once
#include "SpriteRenderer.h"
#include "GameObject.h"
#include <vector>

class GameLevel
{

	GameLevel();

	void Load(const char* file, int lvlWidth, int lvlHeight);
	void Draw(SpriteRender &renderer);
	bool IsCompleted();

private:
	std::vector<GameObject> _gameObjects;
};