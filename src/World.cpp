#include "World.h"
#include "GameObject.h"

void World::AddGameObject(GameObject & obj)
{
	_gameObjects.push_back(obj);
}

void World::RemoveObject(GameObject & obj)
{
	_gameObjects.erase();
}

std::vector<GameObject>& World::GetGameObjects()
{
	return _gameObjects;
}

void World::Update(float dt)
{
	for (auto obj : _gameObjects)
		obj.Update(dt, *this);
}

void World::Render(SpriteRender & renderer)
{
	for (auto obj : _gameObjects)
		obj.Draw(renderer);
}
