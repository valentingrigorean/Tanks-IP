#pragma once
#include "SpriteRenderer.h"
#include "GameObject.h"
#include <vector>

class GameLevel
{
public:
	GameLevel();

	void Load(std::string& file, int lvlWidth, int lvlHeight);
	void Draw(SpriteRender &renderer);
	bool IsCompleted();

	std::vector<GameObject> & GetGameObjects();
private:
	std::vector<GameObject> _gameObjects;
};