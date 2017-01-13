#include <tank/LevelGame.h>

#include <tank/io/GFile.h>
#include <tank/graphics/Point.h>
#include <tank/graphics/Size.h>
#include <tank/ResourceManager.h>

#include <tank/BodyFactory.h>
#include <tank/ComponentsFactory.h>
#include <tank/GConstants.h>
#include <tank/ObjectPool.h>


LevelGame::LevelGame() :_physicsWorld(b2Vec2_zero)
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
			std::string texture = "";
			TILE_TYPE tileType;
			switch (tileCode)
			{
			case '#':
				texture = "s2";
				tileType = TILE_TYPE::SOLID;
				break;
			case '1':
				texture = "s1";
				tileType = TILE_TYPE::SOLID;
				break;
			case '2':
				texture = "b1";
				tileType = TILE_TYPE::DESTROYABLE;
				break;
			case 't':
				texture = "t";
				tileType = TILE_TYPE::DYNAMIC;
				break;
			}

			auto entity = ComponentsFactory::CreateSprite(_ecsWorld, ResourceManager::GetTexture(texture), pos, size);
			uint16 categoryBits = tileType;
			uint16 maskBits = 0x1;
			bool dynamic = false;
			float scale = 1.f;

			switch (tileType)
			{
			case SOLID:
				maskBits = TILE_TYPE::DYNAMIC;
				break;
			case DESTROYABLE:
				maskBits = TILE_TYPE::DYNAMIC;
				ComponentsFactory::AddHealth(entity, 1);
				break;
			case DYNAMIC:
				maskBits = TILE_TYPE::DYNAMIC | TILE_TYPE::SOLID | TILE_TYPE::DESTROYABLE;
				ComponentsFactory::AddTank(entity);
				_tanks.push_back(entity);
				dynamic = true;
				scale = 0.95f;
				break;
			}
			auto obj = ObjectPool::GetObject();
			obj->entity = entity;

			BodyConfig bodyConfig(pos, size, categoryBits, maskBits);
			bodyConfig.dynamic = dynamic;
			bodyConfig.scale = scale;
			ComponentsFactory::AddBody(_physicsWorld,entity,bodyConfig,obj);
		}
	}	
}