#pragma once

#include <anax/System.hpp>
#include "../components/TransformComponent.h"
#include "../components/VelocityComponent.h"

class MovementSystem:anax::System<anax::Requires<TransformComponent, VelocityComponent>>
{
public:
	void Update(double deltaTime);
};

