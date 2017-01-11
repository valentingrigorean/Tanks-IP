#pragma once
#include <anax/World.hpp>
#include <Box2D/Box2D.h>

struct WorldConfig
{
	anax::World ecsWorld;
	b2World physicsWorld;

	WorldConfig() :physicsWorld(b2Vec2(0, 0))
	{
	};
};