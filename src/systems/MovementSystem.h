#pragma once

#include <anax/System.hpp>

struct TransformComponent;
struct VelocityComponent;

class MovementSystem : public anax::System<anax::Requires<TransformComponent, VelocityComponent>>
{
public:
	MovementSystem();
	void Update(double deltaTime);
};

