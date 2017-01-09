#pragma once
#include <vector>
#include <anax/World.hpp>
#include "Texture2D.h"
#include "Size.h"
#include "Point.h"

class Factory
{
public:
	//returns an arrays of tanks to configure more
	static std::vector<anax::Entity> LoadLevel(anax::World& world,std::string& file, int lvlWidth, int lvlHeight);	
	static anax::Entity CreateTank(anax::World& world, Texture2D texture, Point pos, Size size);
	static anax::Entity CreateBullet(anax::World& world, anax::Entity& owner);
private:
	static void CreateTile(anax::World& world, Texture2D texture, Point pos, Size size);
	Factory();	
};