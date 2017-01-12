#pragma once

#include <anax/Component.hpp>

struct GunComponent :anax::Component
{
	bool shooting;
	float timeSinceLastShot;
	float bulletLifeTime;
	int bulletDamage;
	float minimumShotInterval = 0.5f;
};