#pragma once

#include <anax/Component.hpp>
#include "../Rect.h"

struct CollisionComponent : anax::Component
{
	Rect boudingBox;
	bool causeEvents;
};