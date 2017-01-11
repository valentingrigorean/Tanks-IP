#pragma once
#include <anax/Component.hpp>

struct Keys
{
	int up;
	int down;
	int left;
	int right;
	int shot;

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