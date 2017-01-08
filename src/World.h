#pragma once
#include "SpriteRenderer.h"
#include <vector>

class GameObject;

class World
{
public:
	void AddGameObject(GameObject &obj);
	void RemoveObject(GameObject &obj);
	std::vector<GameObject>& GetGameObjects();

	void Update(float dt);
	void Render(SpriteRender& renderer);
private:
	std::vector<GameObject> _gameObjects;
};