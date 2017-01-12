#pragma once

#include <anax/Entity.hpp>
#include <Box2D/Box2D.h>

#include "graphics/Point.h"
#include "graphics/Size.h"

enum TILE_TYPE
{
	SOLID = 0x2,
	DESTROYABLE = SOLID << 1,
	// will causeEvents / movable
	DYNAMIC = DESTROYABLE << 1
};

struct GameObject
{
	Point position;
	Size size;
	TILE_TYPE tileType;
	anax::Entity entity;

	GameObject();

	void Kill(b2World *world);
};