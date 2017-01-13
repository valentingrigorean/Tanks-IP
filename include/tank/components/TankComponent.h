#pragma once
#include <anax/Component.hpp>

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct TankComponent : anax::Component
{	
	float speed = 0.f;
	DIRECTION direction = UP;
	bool idle = true;
};