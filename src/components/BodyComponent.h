#pragma once
#include <anax/Component.hpp>
#include <Box2D/Box2D.h>

struct BodyComponent:anax::Component
{
	b2Body* body;
};