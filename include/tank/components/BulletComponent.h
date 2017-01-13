#pragma once

#include <anax/Component.hpp>
#include <anax/Entity.hpp>


struct BulletComponent :anax::Component
{
	float lifeRemaining = 5.f;
	int dmg;
	anax::Entity owner;
};