#include "GameLevel.h"
#include "io/GFile.h"
#include "ResourceManager.h"

GameLevel::GameLevel()
{
}

void GameLevel::Load(std::string& file, int lvlWidth, int lvlHeight)
{
	_gameObjects.clear();
	auto lines = GFile::ReadAllLines(file.c_str());
	auto width = lines[0].size();
	auto height = lines.size();
	auto unitWidth = lvlWidth / (float)width;
	auto unitHeight = lvlHeight / (float)height;
	for (int y = 0; y < height; y++)
	{
		auto line = lines[y];
		for (int x = 0; x < width; x++)
		{
			auto tileCode = line[x];
			if (tileCode == '.') continue;
			GameObject obj(Point(unitWidth * x, unitHeight *y),
				Size((int)unitWidth, (int)unitHeight));
			switch (tileCode)
			{
			case '#':
				obj.SetSprite(ResourceManager::GetTexture("s2"));
				obj.SetSolid(true);
				break;
			case '1':
				obj.SetSprite(ResourceManager::GetTexture("s1"));
				obj.SetSolid(true);
				break;
			case '2':
				obj.SetSprite(ResourceManager::GetTexture("b1"));
				break;
			case 't':
				obj.SetSprite(ResourceManager::GetTexture("t"));
				break;
			default:
				break;
			}
			_gameObjects.push_back(obj);
		}
	}
}

void GameLevel::Draw(SpriteRender & renderer)
{
	for (auto obj : _gameObjects)
		renderer.DrawSprite(obj.GetSprite(), obj.GetTransform());
}

bool GameLevel::IsCompleted()
{
	return false;
}

std::vector<GameObject>& GameLevel::GetGameObjects()
{
	return _gameObjects;
}
