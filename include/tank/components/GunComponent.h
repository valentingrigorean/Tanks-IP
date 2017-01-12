#pragma once

#include <anax/Component.hpp>
#include <tank/components/TankComponent.h>

struct GunComponent : anax::Component
{
	const float SPEED = 200.f;
	bool shooting;
	float timeSinceLastShot;
	float bulletLifeTime = 5.f;
	int bulletDamage;
	float minimumShotInterval = 0.5f;
	DIRECTION direction;
};