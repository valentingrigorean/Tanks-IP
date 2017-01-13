#pragma once

#include <anax/System.hpp>

#include <tank/components/BulletComponent.h>

class BulletAgeSystem :public anax::System<anax::Requires<BulletComponent>>
{
public:

	void Update(float dt);
};