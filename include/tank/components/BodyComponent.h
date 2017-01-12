#pragma once
#include <anax/Component.hpp>
#include <Box2D/Box2D.h>

struct BodyComponent:anax::Component
{
	bool causeEvents;
	b2Body* body;
};