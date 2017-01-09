#pragma once
#include "../Sprite.h"
#include <anax/Component.hpp>

struct SpriteComponent :anax::Component
{
	Sprite sprite;
};