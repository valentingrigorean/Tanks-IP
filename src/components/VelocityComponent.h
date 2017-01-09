#pragma once
#include "../Point.h"
#include <anax/Component.hpp>
#include <glm/glm.hpp>

struct VelocityComponent :anax::Component
{
	glm::vec2 velocity;
};