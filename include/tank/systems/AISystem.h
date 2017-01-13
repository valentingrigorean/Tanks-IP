#pragma once

#include <anax/System.hpp>
#include <tank/components/AIComponent.h>
#include <tank/components/GunComponent.h>
#include <tank/components/TankComponent.h>
#include <tank/components/BodyComponent.h>
#include <tank/GRandom.h>
#

class AISystem :public anax::System<anax::Requires<AIComponent>>
{
public:
	void Update(float dt);
private:
	void RandomAction(anax::Entity& entity);
	void SetDirection(DIRECTION dir, b2Body *body,float speed);
private:
	enum ACTION_TYPE
	{
		NONE,
		DIR,
		SHOT
	};
	GRandom _random;
};