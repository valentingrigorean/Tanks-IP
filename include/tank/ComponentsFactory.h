#pragma once
#include <anax/Entity.hpp>
#include <anax/World.hpp>
#include "graphics/Texture2D.h"
#include "graphics/Point.h"
#include "graphics/Size.h"
#include "GameObject.h"

class ComponentsFactory
{
public:
	static anax::Entity CreateSprite(anax::World & world, Texture2D& texture, Point position, Size size);
	static void AddBody(b2World& world, GameObject &obj, void *userData = nullptr);
	static void AddTank(anax::Entity &entity, int health = 5, int dmg = 1, float speed = 25.f);
	static void AddHealth(anax::Entity &entity, int health);
private:
	ComponentsFactory();
};