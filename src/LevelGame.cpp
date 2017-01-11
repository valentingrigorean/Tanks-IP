#include "LevelGame.h"

#include "io/GFile.h"
#include "Point.h"
#include "Size.h"
#include "ResourceManager.h"
#include "BodyFactory.h"

#include "GConstants.h"

#include "components/SpriteComponent.h"
#include "components/TankComponent.h"
#include "components/BodyComponent.h"
#include "components/TransformComponent.h"


LevelGame::LevelGame():_physicsWorld(b2Vec2_zero)
{

}

LevelGame::~LevelGame()
{
	_ecsWorld.clear();
}

anax::World & LevelGame::EcsWorld()
{
	return _ecsWorld;
}

b2World & LevelGame::PhysicsWorld()
{
	return _physicsWorld;
}

std::vector<anax::Entity> LevelGame::GetTanks() const
{
	return _tanks;
}

LevelGame * LevelGame::LoadLevel(std::string path, int levelWith, int levelHeight)
{
	LevelGame *level = new LevelGame();
	level->LoadLevelInternal(path, levelWith, levelHeight);
	return level;
}

void LevelGame::LoadLevelInternal(std::string path, int levelWith, int levelHeight)
{	
	auto lines = GFile::ReadAllLines(path.c_str());
	auto height = lines.size();
	auto unitWidth = 40.f;
	auto unitHeight = 40.f;
	for (int y = 0; y < height; y++)
	{
		auto line = lines[y];
		auto width = line.size();
		for (int x = 0; x < width; x++)
		{
			auto tileCode = line[x];
			if (tileCode == '.') continue;
			Point pos(unitWidth * x, unitHeight *y);
			Size size((int)unitWidth, (int)unitHeight);
			switch (tileCode)
			{
			case '#':
				CreateEntity(ResourceManager::GetTexture("s2"), pos, size,false);
				break;
			case '1':
				CreateEntity(ResourceManager::GetTexture("s1"), pos, size,false);
				break;
			case '2':
				CreateEntity(ResourceManager::GetTexture("b1"), pos, size, false);
				break;
			case 't':
				auto tank = CreateEntity(ResourceManager::GetTexture("t"), pos, size,true);		
				tank.addComponent<TankComponent>();
				_tanks.push_back(tank);
				break;
			}
		}
	}	
}

anax::Entity LevelGame::CreateEntity(Texture2D texture, Point pos, Size size,bool dynamicBody)
{
	auto& e = _ecsWorld.createEntity();
	e.addComponent<SpriteComponent>().sprite.SetTexture(texture);

	auto& transform = e.addComponent<TransformComponent>().transform;
	transform.SetPosition(pos);
	transform.SetSize(size);

	auto body = BodyFactory::CreateRect(_physicsWorld, pos.x, pos.y, size.width, size.height, dynamicBody);

	_allEntities.push_back(e);
	body->SetUserData(&_allEntities[_allEntities.size()-1]);

	e.addComponent<BodyComponent>().body = body;
	e.activate();
	return e;
}