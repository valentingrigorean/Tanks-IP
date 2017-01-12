#pragma once

#include <anax/Component.hpp>
#include <anax/Entity.hpp>


struct BulletComponent :anax::Component
{
	float lifeRemaining;
	int dmg;
	anax::Entity owner;
};