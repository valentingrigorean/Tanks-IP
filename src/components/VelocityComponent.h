#pragma once
#include "../Point.h"
#include <anax/Component.hpp>
#include <glm/glm.hpp>

struct VelocityComponent : anax::Component
{
	float speed = 50.f;
	glm::vec2 velocity;
};