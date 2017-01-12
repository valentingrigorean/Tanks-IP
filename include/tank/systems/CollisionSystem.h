#pragma once
#include <anax/System.hpp>
#include <anax/Component.hpp>
#include <map>
#include "PhysicsSystem.h"


class CollisionSystem :
	public anax::System<anax::Requires<anax::Component>>,
	PhysicsSystem::ICollisionListener
{
public:
	void Update();
	void SetPWorld(b2World *world);
	b2World* GetPWorld();
private:
	void OnCollisionOccured(anax::Entity* e1, anax::Entity* e2);
private:
	b2World *_world;
	std::map<anax::Entity*, anax::Entity*> _collisions;
};