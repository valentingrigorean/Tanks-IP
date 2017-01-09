#pragma once
#include <anax/Component.hpp>

struct Keys
{
	char up;
	char down;
	char left;
	char right;
	char shot;

	Keys()
	{
		up = 'W';
		down = 'S';
		left = 'A';
		right = 'D';
		shot = 'E';
	}
};

struct InputComponent : anax::Component
{
	Keys keys;
};