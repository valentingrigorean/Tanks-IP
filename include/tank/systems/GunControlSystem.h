#pragma once
#include <anax/System.hpp>
#include <tank/components/GunComponent.h>

class GunControlSystem :public anax::System<anax::Requires<GunComponent>>
{
public:
	GunControlSystem();
	void Update(float dt);
};