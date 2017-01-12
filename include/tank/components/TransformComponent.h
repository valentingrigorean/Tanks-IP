#pragma once

#include "../graphics/Transform2D.h"
#include <anax/Component.hpp>

struct TransformComponent : anax::Component
{
	Transform2D transform;
};