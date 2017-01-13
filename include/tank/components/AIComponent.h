#pragma once

#include <anax/Component.hpp>

struct AIComponent :anax::Component
{
	float timeSinceUpdate;
	float minimumInterval = 1.f;
};