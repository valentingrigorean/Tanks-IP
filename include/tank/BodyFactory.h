#pragma once
#include <Box2D/Box2D.h>
#include "GameObject.h"

class BodyFactory
{
public:
	static b2Body* CreateRect(b2World &world, float x, float y, int w, int h, TILE_TYPE tileType);
private:
	BodyFactory();
};