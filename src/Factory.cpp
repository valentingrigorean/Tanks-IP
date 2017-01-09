#include <anax/World.hpp>
#include "io/GFile.h"
#include "ResourceManager.h"

#include "Factory.h"
#include "components/SpriteComponent.h"
#include "components/CollisionComponent.h"
#include "components/TransformComponent.h"

std::vector<anax::Entity> Factory::LoadLevel(anax::World & world, std::string & file, int lvlWidth, int lvlHeight)
{
	std::vector<anax::Entity> tanks;
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
			Point pos(unitWidth * x, unitHeight *y);
			Size size((int)unitWidth, (int)unitHeight);			
			switch (tileCode)
			{
			case '#':
				CreateTile(world, ResourceManager::GetTexture("s2"), pos, size);				
				break;
			case '1':
				CreateTile(world, ResourceManager::GetTexture("s1"), pos, size);			
				break;
			case '2':
				CreateTile(world, ResourceManager::GetTexture("b1"), pos, size);
				break;
			case 't':
				tanks.push_back(CreateTank(world, ResourceManager::GetTexture("t"), pos, size));
				break;
			default:
				break;
			}
			
		}
	}
	return tanks;
}

anax::Entity Factory::CreateTank(anax::World & world, Texture2D texture, Point pos, Size size)
{
	auto& e = world.createEntity();
	e.addComponent<SpriteComponent>().sprite.SetTexture(texture);
	auto& transform = e.addComponent<TransformComponent>().transform;
	transform.SetPosition(pos);
	transform.SetSize(size);
	e.addComponent<CollisionComponent>().boudingBox = Rect(pos, size);
	e.activate();
	return e;
}

anax::Entity Factory::CreateBullet(anax::World & world, anax::Entity & owner)
{
	auto& e = world.createEntity();	
	e.activate();
	return e;
}

void Factory::CreateTile(anax::World & world, Texture2D texture, Point pos, Size size)
{
	auto& e = world.createEntity();
	e.addComponent<SpriteComponent>().sprite.SetTexture(texture);
	auto& transform = e.addComponent<TransformComponent>().transform;
	transform.SetPosition(pos);
	transform.SetSize(size);
	e.addComponent<CollisionComponent>().boudingBox = Rect(pos, size);
	e.activate();
}

