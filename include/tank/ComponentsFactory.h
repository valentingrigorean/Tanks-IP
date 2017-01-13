#pragma once
#include <anax/Entity.hpp>
#include <anax/World.hpp>
#include "graphics/Texture2D.h"
#include "graphics/Point.h"
#include "graphics/Size.h"
#include "GameObject.h"
#include "components/GunComponent.h"
#include "BodyFactory.h"

class ComponentsFactory
{
public:
	static anax::Entity CreateSprite(anax::World & world, Texture2D& texture, Point position, Size size);
	static b2Body* AddBody(b2World& world,anax::Entity &entity,BodyConfig &config, void *userData = nullptr,bool causeEvents = false);	
	static void AddTank(anax::Entity &entity, int health = 5, int dmg = 1, float speed = 25.f);
	static void AddHealth(anax::Entity &entity, int health);
	static void CreateBullet(anax::Entity& owner, GunComponent& gunComp);
private:
	ComponentsFactory();
};