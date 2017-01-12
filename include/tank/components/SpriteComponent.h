#pragma once
#include "../graphics/Sprite.h"
#include <anax/Component.hpp>

struct SpriteComponent :anax::Component
{
	Sprite sprite;
};