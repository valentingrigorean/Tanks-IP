#pragma once
#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "graphics/Point.h"
#include "graphics/Size.h"

struct BodyConfig
{
	unsigned short categoryBits = 0x1;
	unsigned short maskBits = 0x1;
	float scale = 1.f;
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;

	bool dynamic = false;

	BodyConfig()
	{
		
	}

	BodyConfig(Point & pos, Size &size, unsigned short _categoryBits, unsigned short _maskBits):
		x(pos.x),y(pos.y),
		w((float)size.width),h((float)size.height),
		categoryBits(_categoryBits),maskBits(_maskBits)
	{

	}
};

class BodyFactory
{
public:
	static b2Body* CreateRect(b2World &world, BodyConfig& config);
private:
	BodyFactory();
};