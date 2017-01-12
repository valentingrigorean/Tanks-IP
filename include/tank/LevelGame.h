#pragma once
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <anax/Entity.hpp>
#include <vector>
#include <map>

#include "GameObject.h"

#include "graphics/Texture2D.h"


class LevelGame
{
public:
	~LevelGame();

	anax::World& EcsWorld();
	b2World& PhysicsWorld();

	std::vector<anax::Entity> GetTanks() const;

	static LevelGame* LoadLevel(std::string path, int levelWith, int levelHeight);

private:
	LevelGame();
	void LoadLevelInternal(std::string path, int levelWith, int levelHeight);	
private:
	std::vector<anax::Entity> _tanks;
	anax::World _ecsWorld;
	b2World _physicsWorld;
};